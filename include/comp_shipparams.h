#ifndef _COMPONENT_SHIP_PARAMS_H
#define _COMPONENT_SHIP_PARAMS_H

#include "component.h"

#include "types.h"

class Sprite;

class CCompShipParams: public CComponent {
public:
	CCompShipParams(CEntity * et, int16 linear, int16 angular,
		float energy, float energyChargeRate, uint16 hitpoints);

	virtual void ReceiveMessage(SMessage &msg);
	virtual void Update(float elapsed);
private:
	int16 m_linearSpeed, m_angularSpeed, m_hitPoints;
	const float m_maxEnergy;
	float m_energy, m_energyChargeRate;
	bool m_isAI;
};

#endif //!_COMPONENT_SHIP_PARAMS_H