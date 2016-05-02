#include <iostream>

#include "../include/comp_projectilemove.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../include/math.h"
#include "../include/screen.h"
#include "../include/world.h"

CCompProjectileMove::~CCompProjectileMove() {}

CCompProjectileMove::CCompProjectileMove(CEntity * et, float linSpeed, float angSpeed):
CComponent(et), m_linSpeed(linSpeed), m_angSpeed(angSpeed) {
	SetType(EC_PROJECTILE_MOVE);
}

void CCompProjectileMove::ReceiveMessage(SMessage &) {
	//if linSpeed and/or angSpeed are changed -> add set message and set them here
}

void CCompProjectileMove::Update(float elapsed) {
	SGetRotMsg getAngMsg;
	m_owner->ReceiveMessage(getAngMsg);
	float angle = 0;
	if(getAngMsg.Modified()) {
		angle = getAngMsg.GetAngle();
	}
	float speed = 100.f;

	SUpdatePosMsg updatePosMsg(static_cast<float>(DegCos(angle) * elapsed * speed),
		static_cast<float>(-DegSin(angle) * elapsed * speed));
	m_owner->ReceiveMessage(updatePosMsg);
	SGetPosMsg getPosMsg;
	m_owner->ReceiveMessage(getPosMsg);
	if(getPosMsg.GetX() > Screen::Instance().GetWidth() || getPosMsg.GetX() < 0 ||
	getPosMsg.GetY() > Screen::Instance().GetHeight() || getPosMsg.GetY() < 0) {
		SGetWorldMsg getWorld;
		m_owner->ReceiveMessage(getWorld);
		getWorld.GetWorld()->DeleteEntity(this->m_owner);
	}
}