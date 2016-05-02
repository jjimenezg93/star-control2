#ifndef _COMP_CHOPPY_THROWER_H
#define _COMP_CHOPPY_THROWER_H

#include "../include/comp_weapon.h"
#include "types.h"

class CCompChoppyThrower: public CCompWeapon {
public:
	CCompChoppyThrower(CEntity * const et, Image * img,	uint8 id, float energyConsumed,
		float lifeTime, float cooldown, uint16 damage, float speed);

	virtual void ReceiveMessage(SMessage &ev);
	virtual void Update(float elapsed);
private:
	float m_botLifeTime;
	float m_speed;
};

#endif //!_COMP_CHOPPY_THROWER_H