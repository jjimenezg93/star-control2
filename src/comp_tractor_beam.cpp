#include <iostream>

#include "../include/audiobuffer.h"
#include "../include/audiosource.h"
#include "../include/comp_tractor_beam.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/image.h"
#include "../include/entities_factory.h"
#include "../include/messages.h"
#include "../include/world.h"

CCompTractorBeam::CCompTractorBeam(CEntity * et, Image * img, uint8 id, float energyConsumed,
float lifeTime, float cooldown, uint16 damage, float attracFactor):
CCompWeapon(et, img, id, energyConsumed, cooldown, damage),
m_decoyLifeTime(lifeTime), m_attractFactor(attracFactor) {
	SetType(EC_TRACTOR_BEAM);
	m_lastShot = cooldown;
}

void CCompTractorBeam::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_SHOOT && m_lastShot >= GetCooldown()) {
		SShootMsg &shootMsg = static_cast<SShootMsg &>(msg);
		if (shootMsg.GetWeaponId() == GetId()) {
			SGetWorldMsg worldMsg;
			m_owner->ReceiveMessage(worldMsg);
			CWorld * world = worldMsg.GetWorld();
			SGetRotMsg rotMsg;
			m_owner->ReceiveMessage(rotMsg);
			SGetPosMsg posMsg;
			m_owner->ReceiveMessage(posMsg);
			SGetEnergyMsg getEnergyMsg;
			m_owner->ReceiveMessage(getEnergyMsg);
			if (rotMsg.Modified() && getEnergyMsg.Modified() &&
				getEnergyMsg.GetEnergy() - GetEnergyConsumed() > 0) {
				world->AddEntity(world->GetEntitiesFactory().SpawnEntity(
					new SDecoyParams(m_owner->GetSide(), GetImg(),
						posMsg.GetX(), posMsg.GetY(), rotMsg.GetAngle(),
						m_decoyLifeTime, GetDamage(), m_attractFactor)));
				SUpdateEnergyMsg updateEnergyMsg(-static_cast<float>(GetEnergyConsumed()));
				m_owner->ReceiveMessage(updateEnergyMsg);
				m_lastShot = 0;
				AudioBuffer * buffer = new AudioBuffer("data/sounds/fusion_blaster_shoot.wav");
				AudioSource * shootAudio = new AudioSource(buffer);
				shootAudio->Play();
			}
		}
	}
}

void CCompTractorBeam::Update(float elapsed) {
	m_lastShot += elapsed;
}

void CCompTractorBeam::Render() {}