#include <assert.h>

#include "../include/comp_projparams.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/event.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"

CCompProjParams::CCompProjParams(CEntity * et): CComponent(et) {
	SetType(EC_PROJ_PARAMS);
}

void CCompProjParams::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_GET_ENTITY_TYPE) {
		SGetEntityTypeMsg &eTypeMsg = static_cast<SGetEntityTypeMsg &>(msg);
		assert(!eTypeMsg.Modified() && "Entity type already modified");
		eTypeMsg.SetType(EET_PROJECTILE);
	}
}

void CCompProjParams::Update(float elapsed) {

}

void CCompProjParams::Render() {

}