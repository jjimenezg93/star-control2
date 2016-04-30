#include <assert.h>

#include "../include/audiobuffer.h"
#include "../include/audiosource.h"
#include "../include/comp_shipparams.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/event.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"
#include "../../include/world.h"

CCompShipParams::CCompShipParams(CEntity * et, int16 linear, int16 angular,
float energy, float energyChargeRate, uint16 hitpoints): CComponent(et), m_linearSpeed(linear),
m_angularSpeed(angular), m_maxEnergy(energy), m_energy(energy),
m_energyChargeRate(energyChargeRate), m_hitPoints(hitpoints) {
	SetType(EC_SHIP_PARAMS);
}

void CCompShipParams::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_GET_ENTITY_TYPE) {
		SGetEntityTypeMsg &eTypeMsg = static_cast<SGetEntityTypeMsg &>(msg);
		assert(!eTypeMsg.Modified() && "Entity type already modified");
		eTypeMsg.SetType(EET_SHIP);
	} else if (msg.m_type == EMT_GET_HP) {
		 SGetHitPointsMsg &getHPMsg = reinterpret_cast<SGetHitPointsMsg &>(msg);
		 getHPMsg.SetHitPoints(m_hitPoints);
	} else if (msg.m_type == EMT_UPDATE_HP) {
		SUpdateHitPointsMsg &updateHPMsg = reinterpret_cast<SUpdateHitPointsMsg &>(msg);
		if (m_hitPoints + updateHPMsg.m_damage <= 0) {
			AudioBuffer * buffer = new AudioBuffer("data/sounds/explosion2.wav");
			AudioSource * source = new AudioSource(buffer);

			SGetPosMsg getPosMsg;
			m_owner->ReceiveMessage(getPosMsg);
			SGetRotMsg getRotMsg;
			m_owner->ReceiveMessage(getRotMsg);
			SGetWorldMsg getWorldMsg;
			m_owner->ReceiveMessage(getWorldMsg);
			assert(getWorldMsg.Modified());
			getWorldMsg.GetWorld()->DeleteEntity(m_owner);

			source->Play();
			SExplosionParams * explParams = new SExplosionParams("explosion1", EGS_NEUTRAL,
				getPosMsg.GetX(), getPosMsg.GetY(), getRotMsg.GetAngle());
			getWorldMsg.GetWorld()->AddEntity(
				getWorldMsg.GetWorld()->GetEntitiesFactory().SpawnEntity(explParams));
		} else
			m_hitPoints += updateHPMsg.m_damage;
	} else if (msg.m_type == EMT_GET_ENERGY) {
		SGetEnergyMsg &getEnergyMsg = reinterpret_cast<SGetEnergyMsg &>(msg);
		getEnergyMsg.SetEnergy(m_energy);
	} else if (msg.m_type == EMT_UPDATE_ENERGY) {
		SUpdateEnergyMsg &updateEnergyMsg = reinterpret_cast<SUpdateEnergyMsg &>(msg);
		if (m_energy + updateEnergyMsg.m_energy >= 0)
			m_energy += updateEnergyMsg.m_energy;
	} else if (msg.m_type == EMT_GET_LINEAR_SPEED) {
		SGetLinSpeedMsg &getLinSpeedMsg = reinterpret_cast<SGetLinSpeedMsg &>(msg);
		getLinSpeedMsg.SetLinSpeed(m_linearSpeed);
	} else if (msg.m_type == EMT_GET_ANGULAR_SPEED) {
		SGetAngSpeedMsg &getAngSpeedMsg = reinterpret_cast<SGetAngSpeedMsg &>(msg);
		getAngSpeedMsg.SetAngSpeed(m_angularSpeed);
	}
}

void CCompShipParams::Update(float elapsed) {
	//charge energy over time
	if (m_energy < m_maxEnergy) {
		m_energy += m_energyChargeRate * elapsed;
	}
	if (m_energy > m_maxEnergy) {
		m_energy = m_maxEnergy;
	}
}

void CCompShipParams::Render() {
	
}