#ifndef _COMPONENT_SHIP_PARAMS_H
#define _COMPONENT_SHIP_PARAMS_H

#include "component.h"

#include "types.h"

class Sprite;

class CCompShipParams: public CComponent {
public:
	CCompShipParams(CEntity * et, float linear, float angular,
		float energy, uint16 hitpoints);

	virtual void ReceiveMessage(SMessage &msg);
	virtual void Update(float elapsed);
	void Render();
private:
	float m_linearSpeed, m_angularSpeed;
	int16 m_hitPoints, m_energy;
};

#endif //!_COMPONENT_SHIP_PARAMS_H