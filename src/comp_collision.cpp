#include <iostream>
#include <assert.h>

#include "../include/collision.h"
#include "../include/comp_collision.h"
#include "../include/comp_render.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/messages.h"
#include "../include/sprite.h"
#include "../include/world.h"

CCompCollision::CCompCollision(CEntity * et): CComponent(et) {
	SetType(EC_COLLISION);
}

void CCompCollision::ReceiveMessage(SMessage & msg) {
	if (msg.m_type == EMT_IS_COLLISION) {
		SIsCollisionMsg &isColMsg = static_cast<SIsCollisionMsg &>(msg);
		Sprite * otherSprt = isColMsg.GetOther()->GetRenderComp()->GetSprite();
		Sprite * sprt = m_owner->GetRenderComp()->GetSprite();
		if (sprt->CheckCollision(otherSprt)) {
			if (isColMsg.GetOther()->GetType() == EET_SHIP) {
				std::cout << "SHIP! BOOOOOOOM!!!" << std::endl;
				SGetWorldMsg getWorldMsg;
				m_owner->ReceiveMessage(getWorldMsg);
				assert(getWorldMsg.Modified());
				getWorldMsg.GetWorld()->DeleteEntity(isColMsg.GetOther());
				getWorldMsg.GetWorld()->DeleteEntity(m_owner);
			} else if (isColMsg.GetOther()->GetType() == EET_PROJECTILE) {
				std::cout << "PROJECTILE COLLISION" << std::endl;
			}
		}
	}
}

void CCompCollision::Update(float elapsed) {
}

void CCompCollision::Render() {
}