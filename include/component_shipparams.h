#ifndef _COMPONENT_SHIP_PARAMS_H
#define _COMPONENT_SHIP_PARAMS_H

#include "component.h"

#include "types.h"

class Sprite;

class CComponentShipParams: public CComponent {
public:
	CComponentShipParams(CEntity * et, float linear, float angular,
		int16 energy, int16 hitpoints);

	virtual void ReceiveMessage(SMessage * const msg);
	virtual void Update(float elapsed);
	void Render();
private:
	float m_linearSpeed, m_angularSpeed;
	int16 m_energy, m_hitpoints;
};

#endif //!_COMPONENT_SHIP_PARAMS_H