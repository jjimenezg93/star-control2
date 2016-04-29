#include <assert.h>

#include "../include/comp_decoyparams.h"
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/messages.h"
#include "../include/image.h"
#include "../include/resourcemanager.h"
#include "../include/world.h"

CCompDecoyParams::CCompDecoyParams(CEntity * et, float lifeTime):
	CComponent(et), m_lifeTime(lifeTime) {
	m_currentTime = 0.f;
	SetType(EC_EXPL_PARAMS);
}

void CCompDecoyParams::ReceiveMessage(SMessage & msg) {
	if (msg.m_type == EMT_GET_ENTITY_TYPE) {
		SGetEntityTypeMsg &eTypeMsg = static_cast<SGetEntityTypeMsg &>(msg);
		assert(!eTypeMsg.Modified() && "Entity type already modified");
		eTypeMsg.SetType(EET_DECOY);
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
