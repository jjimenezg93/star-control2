#ifndef _COMPONENT_COLLISION_H
#define _COMPONENT_COLLISION_H

#include "component.h"

class Sprite;

class CComponentCollision: public CComponent {
public:
	CComponentCollision(CEntity * et, Sprite * sprt);

	virtual void ReceiveMessage(SMessage * const msg);
	virtual void Update(float elapsed);
private:
	Sprite * m_sprite;
};

#endif //!_COMPONENT_COLLISION_H