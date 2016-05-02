#ifndef _COMP_AI_SHIP_DEFAULT_H
#define _COMP_AI_SHIP_DEFAULT_H

#include "component.h"
#include "types.h"

enum EShipState {
	ESS_MOVE,
	ESS_AIM,
	ESS_ATTACK
};

class CCompAIShipDefault: public CComponent {
public:
	CCompAIShipDefault(CEntity * const et);

	virtual void ReceiveMessage(SMessage &msg);
	virtual void Update(float elapsed);

private:
	void Attack();
	void Aim();
	void Move();

	void RotateToAngle(double desiredAngle);
	
	CEntity * m_enemyShip;
	EShipState m_currentState;
	float m_lastDecision;
	float m_nextDecision;

	float m_destX, m_destY;
	bool m_moving;

};

#endif //!_COMP_AI_SHIP_DEFAULT_H