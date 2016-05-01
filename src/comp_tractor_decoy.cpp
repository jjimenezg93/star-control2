#include <iostream>

#include "../include/audiobuffer.h"
#include "../include/audiosource.h"
#include "../include/comp_tractor_decoy.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/image.h"
#include "../include/entities_factory.h"
#include "../include/messages.h"
#include "../include/world.h"

CCompTractorDecoy::CCompTractorDecoy(CEntity * et, float decoyLifeTime):
	CComponent(et), m_decoyLifeTime(decoyLifeTime) {
	SetType(EC_COMP_TRACTOR_DECOY);

	SGetWorldMsg getWorldMsg;
	m_owner->ReceiveMessage(getWorldMsg);
	assert(getWorldMsg.Modified());
	m_enemyShip = getWorldMsg.GetWorld()->GetEnemyShip(m_owner->GetSide());
}

void CCompTractorDecoy::ReceiveMessage(SMessage &msg) {
	
}

void CCompTractorDecoy::Update(float elapsed) {
	SGetWorldMsg getWorldMsg;
	m_owner->ReceiveMessage(getWorldMsg);
	assert(getWorldMsg.Modified());
	m_enemyShip = getWorldMsg.GetWorld()->GetEnemyShip(m_owner->GetSide());

	if (m_enemyShip) {
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

			SGetAttractFactorMsg getAttractFactor;
			m_owner->ReceiveMessage(getAttractFactor);

			SUpdatePosMsg updatePosMsg(-elapsed * getAttractFactor.GetFactor() * x,
				-elapsed * getAttractFactor.GetFactor() * y);
			m_enemyShip->ReceiveMessage(updatePosMsg);
		}
	}
}
