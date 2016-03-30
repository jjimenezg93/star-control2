#include "../include/component_playercontrol.h"
#include "../include/component_position.h"
#include "../include/component_render.h"
#include "../include/entity.h"
#include "../../include/image.h"
#include "../include/messages.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"
#define PLAYER_SPEED_RATE 10
CComponentPlayerControl::CComponentPlayerControl(CEntity * et) {
	m_owner = et;
}

void CComponentPlayerControl::ReceiveMessage(SMessage * msg) {
	PlayerControlMessage * posMsg = dynamic_cast<PlayerControlMessage *>(msg);
	if (posMsg) {
		//we get updated sprite position
		GetSpriteMessage sprtMsg(nullptr);
		m_owner->ReceiveMessage(&sprtMsg);
		GetSpritePosMessage sprtPosMsg;
		if (sprtPosMsg.m_modified) {
			m_x = sprtPosMsg.m_x;
			m_y = sprtPosMsg.m_y;
		}

		if (sprtMsg.m_modified) { //if modified, it means there is a sprite in the entity
			if (sprtMsg.m_sprt->GetX() > Screen::Instance().GetWidth()
					- sprtMsg.m_sprt->GetImage()->GetWidth()
					* sprtMsg.m_sprt->GetImage()->GetHFrames())
				m_canMoveRight = false;
			else
				m_canMoveRight = true;

			if (sprtMsg.m_sprt->GetX() <= 0)
				m_canMoveLeft = false;
			else
				m_canMoveLeft = true;

			if (sprtMsg.m_sprt->GetY() > Screen::Instance().GetHeight()
					- sprtMsg.m_sprt->GetImage()->GetHeight()
					* sprtMsg.m_sprt->GetImage()->GetVFrames())
				m_canMoveDown = false;
			else
				m_canMoveDown = true;

			if (sprtMsg.m_sprt->GetY() <= 0)
				m_canMoveUp = false;
			else
				m_canMoveUp = true;
		}

		switch (posMsg->m_key) {
		case EDPC_LEFT:
			if (m_canMoveLeft)
				m_owner->ReceiveMessage(new UpdateComponentPosMessage(-PLAYER_SPEED_RATE,
					0, posMsg->m_elapsed));
			break;
		case EDPC_RIGHT:
			if (m_canMoveRight)
				m_owner->ReceiveMessage(new UpdateComponentPosMessage(PLAYER_SPEED_RATE,
					0, posMsg->m_elapsed));
			break;
		case EDPC_UP:
			if (m_canMoveUp)
				m_owner->ReceiveMessage(new UpdateComponentPosMessage(0, -PLAYER_SPEED_RATE,
					posMsg->m_elapsed));
			break;
		case EDPC_DOWN:
			if (m_canMoveDown)
				m_owner->ReceiveMessage(new UpdateComponentPosMessage(0, PLAYER_SPEED_RATE,
					posMsg->m_elapsed));
			break;
		default:
			break;
		}
	}
}

void CComponentPlayerControl::Update(float) {}