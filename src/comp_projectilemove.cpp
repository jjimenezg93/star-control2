#include "../include/comp_projectilemove.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../include/math.h"

CCompProjectileMove::~CCompProjectileMove() {

}

CCompProjectileMove::CCompProjectileMove(CEntity * et, float linSpeed, float angSpeed):
CComponent(et), m_linSpeed(linSpeed), m_angSpeed(angSpeed) {
	SetType(EC_PROJECTILE_MOVE);
}

void CCompProjectileMove::ReceiveMessage(SMessage &msg) {
	if(msg.m_type == EMT_SET_POS) {
		
	}
}

void CCompProjectileMove::Update(float elapsed) {
	SGetAngSpeedMsg angSpeedMsg;
	m_owner->ReceiveMessage(angSpeedMsg);
	float angle = 0;
	if(angSpeedMsg.Modified()) {
		angle = angSpeedMsg.GetAngSpeed();
	}

	SUpdateRotMsg updateRotMsg(angle * elapsed);
	m_owner->ReceiveMessage(updateRotMsg);

	SGetPosMsg getPosMsg;
	m_owner->ReceiveMessage(getPosMsg);
	float x = 0, y = 0;
	if(getPosMsg.Modified()) {
		x = getPosMsg.GetX();
		y = getPosMsg.GetY();
	}

	SUpdatePosMsg updatePosMsg(x * DegCos(angle), y * DegCos(angle));
	m_owner->ReceiveMessage(updatePosMsg);
}