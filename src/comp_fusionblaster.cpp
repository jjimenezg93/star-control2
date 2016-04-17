#include <iostream>
#include "../include/comp_fusionblaster.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/image.h"
#include "../include/entities_factory.h"
#include "../include/messages.h"
#include "../include/world.h"

CCompFusionBlaster::CCompFusionBlaster(CEntity * et, Image * img,
	uint8 id, uint16 energyConsumed, float cooldown): CCompWeapon(et, img, id,
	energyConsumed, cooldown) {
	SetType(EC_FUSION_BLASTER);
	m_lastShot = 0;
}

void CCompFusionBlaster::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_SHOOT && m_lastShot >= GetCooldown()) {
		SShootMsg &shootMsg = static_cast<SShootMsg &>(msg);
		if(shootMsg.GetWeaponId() == GetId()) {
			std::cout << "weapon " << GetId() << " SHOOT!" << std::endl;
			SGetWorldMsg worldMsg;
			m_owner->ReceiveMessage(worldMsg);
			CWorld * world = worldMsg.GetWorld();
			//spawn projectile
			SGetRotMsg rotMsg;
			m_owner->ReceiveMessage(rotMsg);
			SGetPosMsg posMsg;
			m_owner->ReceiveMessage(posMsg);
			SGetEnergyMsg getEnergyMsg;
			m_owner->ReceiveMessage(getEnergyMsg);
			if(rotMsg.Modified() && getEnergyMsg.Modified() && getEnergyMsg.GetEnergy() > 0) {
				world->AddEntity(world->GetEntitiesFactory().SpawnEntity(
					new SProjectileParams(posMsg.GetX(), posMsg.GetY(), 20,
						rotMsg.GetAngle(), m_owner->GetSide(), GetImg())));
				SUpdateEnergyMsg updateEnergyMsg(-GetEnergyConsumed());
				m_owner->ReceiveMessage(updateEnergyMsg);
				m_owner->ReceiveMessage(getEnergyMsg);
			}
			m_lastShot = 0;
		}
	}
}

void CCompFusionBlaster::Update(float elapsed) {
	m_lastShot += elapsed;
}

void CCompFusionBlaster::Render() {}
