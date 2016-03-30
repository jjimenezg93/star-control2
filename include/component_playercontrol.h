#ifndef _COMPONENT_PLAYERCONTROL_H
#define _COMPONENT_PLAYERCONTROL_H

#include "component.h"

class CEntity;
struct SMessage;

class CComponentPlayerControl: public CComponent {
public:
	CComponentPlayerControl(CEntity * et);

	virtual void ReceiveMessage(SMessage * const msg);
	virtual void Update(float elapsed);
private:
	float m_x, m_y;
	bool m_canMoveLeft, m_canMoveRight, m_canMoveUp, m_canMoveDown;
};

#endif //!_COMPONENT_PLAYERCONTROL_H