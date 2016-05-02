#include <iostream>
#include <assert.h>

#include "../include/comp_playercontrol.h"
#include "../include/event.h"
#include "../include/entity.h"
#include "../include/nsinputmanagerentity.h"
#include "../include/messages.h"
#include "../include/math.h"
#include "../include/screen.h"

CCompPlayerControl::CCompPlayerControl(CEntity * et): CComponent(et) {
	SetType(EC_PLAYER_CONTROL);
}

CCompPlayerControl::~CCompPlayerControl() {
	for (uint8 i = 0; i < sizeof(m_controls) / sizeof(m_controls[0]); ++i) {
		IInputManagerEntity::Unregister(m_owner, EEC_KEYBOARD, m_controls[i]);
	}
}

void CCompPlayerControl::ReceiveMessage(SMessage &msg) {
	float elapsed = static_cast<float>(Screen::Instance().ElapsedTime());
	if (msg.m_type == EMT_INPUT) {
		SInputMsg &inputMsg = reinterpret_cast<SInputMsg &>(msg);
		if (inputMsg.GetController() == EEC_KEYBOARD) {
			if (inputMsg.GetId() == m_controls[0]) { //up
				MoveUp(elapsed);
			} else if (inputMsg.GetId() == m_controls[1]) { //down
				MoveDown(elapsed);
			} else if (inputMsg.GetId() == m_controls[2]) { //left
				TurnLeft(elapsed);
			} else if (inputMsg.GetId() == m_controls[3]) { //right
				TurnRight(elapsed);
			} else if (inputMsg.GetId() == m_controls[4]) { //primaryWeapon
				Shoot(0);
			} else if(inputMsg.GetId() == m_controls[5]) { //secondaryWeapon
				Shoot(1);
			}
		}
	} else if (msg.m_type == EMT_AI_INPUT) {
		SAIInputMsg &inputMsg = reinterpret_cast<SAIInputMsg &>(msg);
		if (inputMsg.GetInput() == EAII_UP) { //up
			MoveUp(elapsed);
		} else if (inputMsg.GetInput() == EAII_DOWN) { //down
			MoveDown(elapsed);
		} else if (inputMsg.GetInput() == EAII_LEFT) { //left
			TurnLeft(elapsed);
		} else if (inputMsg.GetInput() == EAII_RIGHT) { //right
			TurnRight(elapsed);
		} else if (inputMsg.GetInput() == EAII_SHOOT_PRIMARY) { //primaryWeapon
			Shoot(0);
		} else if (inputMsg.GetInput() == EAII_SHOOT_SECONDARY) { //secondaryWeapon
			Shoot(1);
		}
	}
}

void CCompPlayerControl::MoveUp(float) {
	float offsetX = 0, offsetY = 0;
	if (GetLinearOffset(offsetX, offsetY)) {
		SUpdatePosMsg updateMsg(offsetX, offsetY);
		m_owner->ReceiveMessage(updateMsg);
	}
}

void CCompPlayerControl::MoveDown(float) {
	float offsetX = 0, offsetY = 0;
	GetLinearOffset(offsetX, offsetY);

	if (GetLinearOffset(offsetX, offsetY)) {
		SUpdatePosMsg updateMsg(-offsetX, -offsetY);
		m_owner->ReceiveMessage(updateMsg);
	}
}

void CCompPlayerControl::TurnLeft(float elapsed) {
	SGetAngSpeedMsg angSpeedMsg;
	m_owner->ReceiveMessage(angSpeedMsg);
	if (angSpeedMsg.Modified()) {
		SUpdateRotMsg updateMsg(
			static_cast<float>(angSpeedMsg.GetAngSpeed() * elapsed));
		m_owner->ReceiveMessage(updateMsg);
	}
}

void CCompPlayerControl::TurnRight(float elapsed) {
	SGetAngSpeedMsg angSpeedMsg;
	m_owner->ReceiveMessage(angSpeedMsg);
	if (angSpeedMsg.Modified()) {
		SUpdateRotMsg updateMsg(
			static_cast<float>(-angSpeedMsg.GetAngSpeed() * elapsed));
		m_owner->ReceiveMessage(updateMsg);
	}
}

void CCompPlayerControl::Shoot(uint8 weaponId) {
	SShootMsg shootMsg(weaponId);
	m_owner->ReceiveMessage(shootMsg);
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
	float speed = 0;
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

void CCompPlayerControl::Update(float) {}

//receives control keys and registers into InputManager
void CCompPlayerControl::SetControls(uint16 controls[kEntityNumControls]) {
	memcpy(m_controls, controls, sizeof(m_controls));

	SGetAIMsg getIsAI;
	m_owner->ReceiveMessage(getIsAI);
	assert(getIsAI.Modified());
	if (!getIsAI.IsAI()) {
		for (uint16 i = 0; i < sizeof(m_controls) / sizeof(m_controls[0]); ++i) {
			IInputManagerEntity::Register(m_owner, EEC_KEYBOARD, m_controls[i]);
		}
	}
}