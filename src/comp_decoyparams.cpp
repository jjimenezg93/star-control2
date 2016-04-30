#include <assert.h>

#include "../include/comp_decoyparams.h"
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/messages.h"
#include "../include/image.h"
#include "../include/resourcemanager.h"
#include "../include/world.h"

CCompDecoyParams::CCompDecoyParams(CEntity * et, float lifeTime, float damage):
	CComponent(et), m_lifeTime(lifeTime), m_damage(damage) {
	m_currentTime = 0.f;
	SetType(EC_DECOY_PARAMS);
}

void CCompDecoyParams::ReceiveMessage(SMessage & msg) {
	if (msg.m_type == EMT_GET_ENTITY_TYPE) {
		SGetEntityTypeMsg &eTypeMsg = static_cast<SGetEntityTypeMsg &>(msg);
		assert(!eTypeMsg.Modified() && "Entity type already modified");
		eTypeMsg.SetType(EET_DECOY);
	} else if (msg.m_type == EMT_GET_DAMAGE) {
		SGetDamageMsg &getDmgMsg = static_cast<SGetDamageMsg &>(msg);
		getDmgMsg.SetDamage(m_damage);
	}
}

void CCompDecoyParams::Update(float elapsed) {
	m_currentTime += elapsed;
	if (m_currentTime >= m_lifeTime) {
		SGetWorldMsg getWorldMsg;
		m_owner->ReceiveMessage(getWorldMsg);
		getWorldMsg.GetWorld()->DeleteEntity(m_owner);
	}
}

void CCompDecoyParams::Render() {}
