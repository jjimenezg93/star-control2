#include <iostream>

#include "../include/collision.h"
#include "../include/comp_collision.h"
#include "../include/comp_render.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../include/sprite.h"

CCompCollision::CCompCollision(CEntity * et): CComponent(et) {
	SetType(EC_COLLISION);
}

void CCompCollision::ReceiveMessage(SMessage & msg) {
	if (msg.m_type == EMT_IS_COLLISION) {
		SIsCollisionMsg &isColMsg = static_cast<SIsCollisionMsg &>(msg);
		Sprite * otherSprt = isColMsg.GetOther()->GetRenderComp()->GetSprite();
		Sprite * sprt = m_owner->GetRenderComp()->GetSprite();
		if (sprt->CheckCollision(otherSprt)) {
			std::cout << "COLLISION!" << std::endl;
		}
	}
}

void CCompCollision::Update(float elapsed) {
}

void CCompCollision::Render() {
}
