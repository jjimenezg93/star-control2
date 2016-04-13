#include <iostream>

#include "../include/comp_playercontrol.h"
#include "../include/event.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../include/math.h"

CCompPlayerControl::CCompPlayerControl(CEntity * et): CComponent(et) {
	SetType(EC_PLAYER_CONTROL);
}

void CCompPlayerControl::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_INPUT) {
		SInputMsg &inputMsg = reinterpret_cast<SInputMsg &>(msg);
		if (inputMsg.m_controller == EEC_KEYBOARD) {
			if (inputMsg.m_id == m_controls[0]) { //up
				SGetRotMsg getRotMsg;
				m_owner->ReceiveMessage(getRotMsg);

				float offsetX = kPosUpdateOffset;
				float offsetY = kPosUpdateOffset;
				if (getRotMsg.Modified()) {
					offsetX *= cos(WrapValue(getRotMsg.m_angle, 360));
					offsetY *= sin(WrapValue(getRotMsg.m_angle, 360));
				}

				SUpdatePosMsg updateMsg(offsetX, offsetY);
				m_owner->ReceiveMessage(updateMsg);
			} else if (inputMsg.m_id == m_controls[1]) { //down
				SUpdatePosMsg updateMsg(0, kPosUpdateOffset);
				m_owner->ReceiveMessage(updateMsg);
			} else if (inputMsg.m_id == m_controls[2]) { //left
				SUpdateRotMsg updateMsg(-kRotationRate);
				m_owner->ReceiveMessage(updateMsg);
			} else if (inputMsg.m_id == m_controls[3]) { //rigth
				SUpdateRotMsg updateMsg(kRotationRate);
				m_owner->ReceiveMessage(updateMsg);
			}
		}
	}
}

void CCompPlayerControl::Update(float elapsed) {
}

void CCompPlayerControl::Render() {
}

void CCompPlayerControl::SetControls(uint16 controls[kEntityNumControls]) {
	memcpy(m_controls, controls, sizeof(m_controls));
}