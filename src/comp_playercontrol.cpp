#include <iostream>

#include "../include/comp_playercontrol.h"
#include "../include/event.h"
#include "../include/entity.h"
#include "../include/messages.h"

CCompPlayerControl::CCompPlayerControl(CEntity * et): CComponent(et) {
	SetType(EC_PLAYER_CONTROL);
}

void CCompPlayerControl::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_INPUT) {
		SInputMessage &inputMsg = reinterpret_cast<SInputMessage &>(msg);
		if (inputMsg.m_controller == EEC_KEYBOARD) {
			if (inputMsg.m_id == m_controls[0]) { //up
				SUpdatePosMessage updateMsg(0, -kPosUpdateOffset);
				m_owner->ReceiveMessage(updateMsg);
			} else if (inputMsg.m_id == m_controls[1]) { //down
				SUpdatePosMessage updateMsg(0, kPosUpdateOffset);
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