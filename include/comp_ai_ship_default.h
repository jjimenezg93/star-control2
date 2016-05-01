#ifndef _COMP_AI_SHIP_DEFAULT_H
#define _COMP_AI_SHIP_DEFAULT_H

#include "component.h"
#include "types.h"

enum EShipState {
	ESS_MOVE,
	ESS_AIM,
	ESS_ATTACK
};

class CCompShipDefault: public CComponent {
public:
	CCompShipDefault(CEntity * const et);

	virtual void ReceiveMessage(SMessage &ev);
	virtual void Update(float elapsed);

private:
	
	CEntity * m_enemyShip;
	EShipState m_currentState;
	float m_lastDecision;
	float m_nextDecision;
};

#endif //!_COMP_AI_SHIP_DEFAULT_H