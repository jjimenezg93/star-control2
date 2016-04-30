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

const float attractionFactor = 50.f;

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
		/*int16 x = getEnemyPosMsg.GetX() - getOwnPosMsg.GetX();
		int16 y = getEnemyPosMsg.GetY() - getOwnPosMsg.GetY();*/

		SUpdatePosMsg updatePosMsg(-elapsed * attractionFactor * x,
			-elapsed * attractionFactor * y);
		m_enemyShip->ReceiveMessage(updatePosMsg);
	}
}

void CCompTractorDecoy::Render() {}
