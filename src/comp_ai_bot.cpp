#include <iostream>

#include "../include/audiobuffer.h"
#include "../include/audiosource.h"
#include "../include/comp_ai_bot.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/image.h"
#include "../include/entities_factory.h"
#include "../include/messages.h"
#include "../include/world.h"

CCompAIBot::CCompAIBot(CEntity * et, float LifeTime):
	CComponent(et), m_lifeTime(LifeTime) {
	SetType(EC_COMP_CHOPPY_BOT);

	SGetWorldMsg getWorldMsg;
	m_owner->ReceiveMessage(getWorldMsg);
	assert(getWorldMsg.Modified());
	m_enemyShip = getWorldMsg.GetWorld()->GetEnemyShip(m_owner->GetSide());
}

void CCompAIBot::ReceiveMessage(SMessage &msg) {

}

void CCompAIBot::Update(float elapsed) {
	SGetPosMsg getEnemyPosMsg;
	m_enemyShip->ReceiveMessage(getEnemyPosMsg);
	if (getEnemyPosMsg.Modified()) {
		SGetPosMsg getOwnPosMsg;
		m_owner->ReceiveMessage(getOwnPosMsg);
		assert(getOwnPosMsg.Modified());

		int16 x, y;
		if (getEnemyPosMsg.GetX() - getOwnPosMsg.GetX() < 0) {
			x = -1;
		} else {
			x = 1;
		}
		if (getEnemyPosMsg.GetY() - getOwnPosMsg.GetY() < 0) {
			y = -1;
		} else {
			y = 1;
		}

		SGetLinSpeedMsg getLinSpeedMsg;
		m_owner->ReceiveMessage(getLinSpeedMsg);
		assert(getLinSpeedMsg.Modified());

		SUpdatePosMsg updatePosMsg(elapsed * getLinSpeedMsg.GetLinSpeed() * x,
			elapsed * getLinSpeedMsg.GetLinSpeed() * y);
		m_owner->ReceiveMessage(updatePosMsg);
	}
}
