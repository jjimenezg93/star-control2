#include <assert.h>

#include "../include/comp_botparams.h"
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/messages.h"
#include "../include/image.h"
#include "../include/resourcemanager.h"
#include "../include/world.h"

CCompBotParams::CCompBotParams(CEntity * et, float lifeTime, float damage, float speed):
	CComponent(et), m_lifeTime(lifeTime), m_damage(damage), m_speed(speed) {
	m_currentTime = 0.f;
	SetType(EC_BOT_PARAMS);
}

void CCompBotParams::ReceiveMessage(SMessage & msg) {
	if (msg.m_type == EMT_GET_ENTITY_TYPE) {
		SGetEntityTypeMsg &eTypeMsg = static_cast<SGetEntityTypeMsg &>(msg);
		assert(!eTypeMsg.Modified() && "Entity type already modified");
		eTypeMsg.SetType(EET_DECOY);
	} else if (msg.m_type == EMT_GET_DAMAGE) {
		SGetDamageMsg &getDmgMsg = static_cast<SGetDamageMsg &>(msg);
		getDmgMsg.SetDamage(m_damage);
	} else if (msg.m_type == EMT_GET_LINEAR_SPEED) {
		SGetLinSpeedMsg &getLinSpeedMsg = static_cast<SGetLinSpeedMsg &>(msg);
		getLinSpeedMsg.SetLinSpeed(m_speed);
	}
}

void CCompBotParams::Update(float elapsed) {
	m_currentTime += elapsed;
	if (m_currentTime >= m_lifeTime) {
		SGetWorldMsg getWorldMsg;
		m_owner->ReceiveMessage(getWorldMsg);
		getWorldMsg.GetWorld()->DeleteEntity(m_owner);
	}
}
