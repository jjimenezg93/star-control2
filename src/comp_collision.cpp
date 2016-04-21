#include <iostream>
#include <assert.h>

#include "../include/audiobuffer.h"
#include "../include/audiosource.h"
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
			if (m_owner->GetType() == EET_SHIP && isColMsg.GetOther()->GetType() == EET_SHIP) {
				std::cout << "SHIP - SHIP" << std::endl;
				AudioBuffer * buffer = new AudioBuffer("data/sounds/explosion3.wav");
				AudioSource * source = new AudioSource(buffer);

				SGetWorldMsg getWorldMsg;
				m_owner->ReceiveMessage(getWorldMsg);
				assert(getWorldMsg.Modified());
				getWorldMsg.GetWorld()->DeleteEntity(isColMsg.GetOther());
				getWorldMsg.GetWorld()->DeleteEntity(m_owner);
				source->Play();
			} else if (m_owner->GetType() == EET_SHIP
			&& isColMsg.GetOther()->GetType() == EET_PROJECTILE) {
				std::cout << "SHIP - PROJECTILE" << std::endl;
				SGetDamageMsg getDmgMsg;
				isColMsg.GetOther()->ReceiveMessage(getDmgMsg);
				if (getDmgMsg.Modified()) {
					SUpdateHitPointsMsg updateHPMsg(-getDmgMsg.GetDamage());
					m_owner->ReceiveMessage(updateHPMsg);
					
					SGetWorldMsg getWorldMsg;
					m_owner->ReceiveMessage(getWorldMsg);
					getWorldMsg.GetWorld()->DeleteEntity(isColMsg.GetOther());
					AudioBuffer * buffer = new AudioBuffer("data/sounds/explosion1.wav");
					AudioSource * source = new AudioSource(buffer);
					source->Play();
				}
			} else if (m_owner->GetType() == EET_PROJECTILE
			&& isColMsg.GetOther()->GetType() == EET_SHIP) {
				std::cout << "PROJECTILE - SHIP" << std::endl;
				SGetDamageMsg getDmgMsg;
				m_owner->ReceiveMessage(getDmgMsg);
				if (getDmgMsg.Modified()) {
					SUpdateHitPointsMsg updateHPMsg(-getDmgMsg.GetDamage());
					isColMsg.GetOther()->ReceiveMessage(updateHPMsg);

					SGetWorldMsg getWorldMsg;
					isColMsg.GetOther()->ReceiveMessage(getWorldMsg);
					getWorldMsg.GetWorld()->DeleteEntity(m_owner);
					AudioBuffer * buffer = new AudioBuffer("data/sounds/explosion1.wav");
					AudioSource * source = new AudioSource(buffer);
					source->Play();
				}
			}/* else if (m_owner->GetType() == EET_PROJECTILE
			&& isColMsg.GetOther()->GetType() == EET_PROJECTILE) {
				std::cout << "PROJECTILE - PROJECTILE" << std::endl;
			}*/
		}
	}
}

void CCompCollision::Update(float elapsed) {
}

void CCompCollision::Render() {
}