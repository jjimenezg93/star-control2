#include <assert.h>

#include "../include/comp_explparams.h"
#include "../include/component.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/messages.h"
#include "../include/image.h"
#include "../include/resourcemanager.h"
#include "../include/world.h"

CCompExplParams::CCompExplParams(CEntity * et, int16 fps, float lifeTime):
CComponent(et), m_fps(fps), m_lifeTime(lifeTime) {
	m_currentTime = 0.f;
	SetType(EC_EXPL_PARAMS);
}

void CCompExplParams::ReceiveMessage(SMessage & msg) {
	if (msg.m_type == EMT_GET_ENTITY_TYPE) {
		SGetEntityTypeMsg &eTypeMsg = static_cast<SGetEntityTypeMsg &>(msg);
		assert(!eTypeMsg.Modified() && "Entity type already modified");
		eTypeMsg.SetType(EET_EXPLOSION);
	}
}

void CCompExplParams::Update(float elapsed) {
	m_currentTime += elapsed;
	if (m_currentTime >= m_lifeTime) {
		SGetWorldMsg getWorldMsg;
		m_owner->ReceiveMessage(getWorldMsg);
		getWorldMsg.GetWorld()->DeleteEntity(m_owner);
	}
}

void CCompExplParams::Render() {
}
