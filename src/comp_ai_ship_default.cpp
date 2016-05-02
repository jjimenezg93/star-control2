#include <assert.h>
#include <cstdlib>

#include "../include/comp_ai_ship_default.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../include/event.h"
#include "../include/world.h"
#include "../include/math.h"
#include "../include/screen.h"

#define ROT_PRECISION_OFFSET 5
#define MOVE_PRECISION_OFFSET 2

CCompAIShipDefault::CCompAIShipDefault(CEntity * const et): CComponent(et),
m_lastDecision(0.f), m_nextDecision(0.f), m_currentState(ESS_MOVE) {
	SetType(EC_AI_SHIP_DEFAULT);
}

void CCompAIShipDefault::ReceiveMessage(SMessage &) {}

void CCompAIShipDefault::Update(float elapsed) {
	m_lastDecision += elapsed;

	switch (m_currentState) {
	case ESS_MOVE:
		Move();
		break;
	case ESS_AIM:
		Aim();
		break;
	case ESS_ATTACK:
		Attack();
		break;
	default:
		break;
	}
}

void CCompAIShipDefault::Attack() {
	uint8 randShoot = rand() % 8;
	uint8 randWeapon = rand() % 1;

	if (!randShoot) {
		SShootMsg shootMsg(randWeapon);
		m_owner->ReceiveMessage(shootMsg);
	}

	m_currentState = ESS_AIM;
}

void CCompAIShipDefault::Aim() {
	SGetWorldMsg getWorldMsg;
	m_owner->ReceiveMessage(getWorldMsg);
	assert(getWorldMsg.Modified());
	m_enemyShip = getWorldMsg.GetWorld()->GetEnemyShip(m_owner->GetSide());
	if (m_enemyShip != nullptr) {
		SGetPosMsg getOwnPosMsg;
		m_owner->ReceiveMessage(getOwnPosMsg);
		SGetPosMsg getEnemyPosMsg;
		m_enemyShip->ReceiveMessage(getEnemyPosMsg);

		double desiredAngle = Angle(getOwnPosMsg.GetX(), getOwnPosMsg.GetY(),
			getEnemyPosMsg.GetX(), getEnemyPosMsg.GetY());

		RotateToAngle(desiredAngle);
	}
	uint8 backToMove = rand() % 30;

	if (!backToMove) {
		m_currentState = ESS_MOVE;
	}
}

void CCompAIShipDefault::RotateToAngle(double desiredAngle) {
	SGetRotMsg getOwnRotMsg;
	m_owner->ReceiveMessage(getOwnRotMsg);
	assert(getOwnRotMsg.Modified());

	double wrapAngle = WrapValue(desiredAngle, 360);

	if (abs(desiredAngle) - WrapValue(getOwnRotMsg.GetAngle(), 360) < ROT_PRECISION_OFFSET
		&& desiredAngle - WrapValue(getOwnRotMsg.GetAngle(), 360) > -ROT_PRECISION_OFFSET) {
		m_currentState = ESS_ATTACK;
	} else {
		double cw = WrapValue(getOwnRotMsg.GetAngle() - wrapAngle, 360);
		double ccw = WrapValue(wrapAngle - getOwnRotMsg.GetAngle(), 360);
		if (min(ccw, cw) == ccw) {
			SAIInputMsg aiInputMsg(EAII_LEFT);
			m_owner->ReceiveMessage(aiInputMsg);
		} else {
			SAIInputMsg aiInputMsg(EAII_RIGHT);
			m_owner->ReceiveMessage(aiInputMsg);
		}
	}
}

void CCompAIShipDefault::Move() {
	if (!m_moving) {
		m_destX = static_cast<float>(rand() %Screen::Instance().GetWidth());
		m_destY = static_cast<float>(rand() % Screen::Instance().GetHeight());
		m_moving = true;
	}
	SGetPosMsg getPosMsg;
	m_owner->ReceiveMessage(getPosMsg);
	assert(getPosMsg.Modified());

	if (m_destX - getPosMsg.GetX() < MOVE_PRECISION_OFFSET
	&& m_destY - getPosMsg.GetY() < MOVE_PRECISION_OFFSET) {
		m_moving = false;
	}

	double desiredAngle = Angle(getPosMsg.GetX(), getPosMsg.GetY(),
		m_destX, m_destY);

	RotateToAngle(desiredAngle);

	SAIInputMsg aiInputMsg(EAII_UP);
	m_owner->ReceiveMessage(aiInputMsg);

	uint8 backToAim = rand() % 6;

	if (!backToAim) {
		m_currentState = ESS_AIM;
	}
}

