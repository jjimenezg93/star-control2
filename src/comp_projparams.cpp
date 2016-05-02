#include <assert.h>

#include "../include/comp_projparams.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/event.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"

#include "../include/comp_render.h"

CCompProjParams::CCompProjParams(CEntity * et, uint16 damage): CComponent(et), m_damage(damage) {
	SetType(EC_PROJ_PARAMS);
	Sprite * sp = m_owner->GetRenderComp()->GetSprite();
	if (strcmp(sp->GetImage()->GetFilename().ToCString(), "data/weapons/blast.png")
		&& strcmp(sp->GetImage()->GetFilename().ToCString(), "data/weapons/rocket.png")) {
		sp = sp;
	}
}

void CCompProjParams::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_GET_ENTITY_TYPE) {
		SGetEntityTypeMsg &eTypeMsg = static_cast<SGetEntityTypeMsg &>(msg);
		assert(!eTypeMsg.Modified() && "Entity type already modified");
		eTypeMsg.SetType(EET_PROJECTILE);
	} else if (msg.m_type == EMT_GET_DAMAGE) {
		SGetDamageMsg &getDmgMsg = static_cast<SGetDamageMsg &>(msg);
		assert(!getDmgMsg.Modified() && "Projectile damage already modified");
		getDmgMsg.SetDamage(m_damage);
	}
}

void CCompProjParams::Update(float) {}