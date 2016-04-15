#include <iostream>

#include "../include/comp_playercontrol.h"
#include "../include/event.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../include/math.h"
#include "../include/screen.h"

CCompPlayerControl::CCompPlayerControl(CEntity * et): CComponent(et) {
	SetType(EC_PLAYER_CONTROL);
}

void CCompPlayerControl::ReceiveMessage(SMessage &msg) {
	double elapsed = Screen::Instance().ElapsedTime();
	if (msg.m_type == EMT_INPUT) {
		SInputMsg &inputMsg = reinterpret_cast<SInputMsg &>(msg);
		if (inputMsg.m_controller == EEC_KEYBOARD) {
			if (inputMsg.m_id == m_controls[0]) { //up
				float offsetX = 0, offsetY = 0;
				if (GetLinearOffset(offsetX, offsetY)) {
					SUpdatePosMsg updateMsg(offsetX, offsetY);
					m_owner->ReceiveMessage(updateMsg);
				}
			} else if (inputMsg.m_id == m_controls[1]) { //down
				float offsetX = 0, offsetY = 0;
				GetLinearOffset(offsetX, offsetY);

				if (GetLinearOffset(offsetX, offsetY)) {
					SUpdatePosMsg updateMsg(-offsetX, -offsetY);
					m_owner->ReceiveMessage(updateMsg);
				}
			} else if (inputMsg.m_id == m_controls[2]) { //left
				SGetAngSpeedMsg angSpeedMsg;
				m_owner->ReceiveMessage(angSpeedMsg);
				if (angSpeedMsg.Modified()) {
					SUpdateRotMsg updateMsg(
						static_cast<float>(angSpeedMsg.GetAngSpeed() * elapsed));
					m_owner->ReceiveMessage(updateMsg);
				}
			} else if (inputMsg.m_id == m_controls[3]) { //right
				SGetAngSpeedMsg angSpeedMsg;
				m_owner->ReceiveMessage(angSpeedMsg);
				if (angSpeedMsg.Modified()) {
					SUpdateRotMsg updateMsg(
						static_cast<float>(-angSpeedMsg.GetAngSpeed() * elapsed));
					m_owner->ReceiveMessage(updateMsg);
				}
			} else if (inputMsg.m_id == m_controls[4]) {
				SShootMsg shootMsg(0);
				m_owner->ReceiveMessage(shootMsg);
			} else if(inputMsg.m_id == m_controls[5]) {
				SShootMsg shootMsg(1);
				m_owner->ReceiveMessage(shootMsg);
			}
		}
	}
}

bool CCompPlayerControl::GetLinearOffset(float &offsetX, float &offsetY) const {
	double elapsed = Screen::Instance().ElapsedTime();
	bool ret = true;

	SGetRotMsg getRotMsg;
	m_owner->ReceiveMessage(getRotMsg);
	float angle = 0;
	if (getRotMsg.Modified())
		angle = getRotMsg.GetAngle();
	else
		ret = false;

	SGetLinSpeedMsg getLinSpeedMsg;
	m_owner->ReceiveMessage(getLinSpeedMsg);
	int16 speed = 0;
	if (getLinSpeedMsg.Modified())
		speed = getLinSpeedMsg.GetLinSpeed();
	else
		ret = false;

	if (getRotMsg.Modified()) {
		offsetX = static_cast<float>(DegCos(WrapValue(angle, 360)) * elapsed * speed);
		offsetY = static_cast<float>(-DegSin(WrapValue(angle, 360)) * elapsed * speed);
	} else
		ret = false;

	return ret;
}

void CCompPlayerControl::Update(float elapsed) {
}

void CCompPlayerControl::Render() {
}

void CCompPlayerControl::SetControls(uint16 controls[kEntityNumControls]) {
	memcpy(m_controls, controls, sizeof(m_controls));
}