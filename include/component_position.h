#ifndef _COMPONENT_POSITION_H
#define _COMPONENT_POSITION_H

#include "component.h"

class CEntity;
struct SMessage;

class CComponentPosition: public CComponent {
public:
	CComponentPosition(CEntity * et, float x, float y);

	virtual void ReceiveMessage(SMessage * const msg);
	virtual void Update(float elapsed);
private:
	float m_x, m_y;
};

#endif //!_COMPONENT_POSITION_H