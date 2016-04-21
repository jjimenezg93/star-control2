#include <assert.h>

#include "../include/comp_shipparams.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/event.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"

CCompShipParams::CCompShipParams(CEntity * et, float linear, float angular,
float energy, uint16 hitpoints): CComponent(et), m_linearSpeed(linear), m_angularSpeed(angular),
m_energy(energy), m_hitPoints(hitpoints) {
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
	
}

void CCompShipParams::Render() {
	
}