#ifndef _COMPONENT_PROJ_PARAMS_H
#define _COMPONENT_PROJ_PARAMS_H

#include "component.h"

#include "types.h"

class Sprite;

class CCompProjParams: public CComponent {
public:
	CCompProjParams(CEntity * et, uint16 damage = 0);

	virtual void ReceiveMessage(SMessage &msg);
	virtual void Update(float elapsed);
private:
	uint16 m_damage;
};

#endif //!_COMPONENT_PROJ_PARAMS_H