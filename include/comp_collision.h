#ifndef _COMP_COLLISION_H
#define _COMP_COLLISION_H

#include "component.h"

class CCompCollision: public CComponent {
public:
	CCompCollision(CEntity * et);

	virtual void ReceiveMessage(SMessage &ev);
	virtual void Update(float elapsed);
};

#endif //!_COMP_COLLISION_H