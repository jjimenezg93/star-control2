#ifndef _COMP_FUSION_BLASTER_H
#define _COMP_FUSION_BLASTER_H

#include "comp_weapon.h"
#include "types.h"

class Image;

class CCompFusionBlaster: public CCompWeapon {
public:
	CCompFusionBlaster(CEntity * const et, Image * img,
		uint8 id, uint16 energyConsumed, float cooldown, uint16 damage);

	virtual void ReceiveMessage(SMessage &ev);
	virtual void Update(float elapsed);
	void Render();
};

#endif //!_COMP_FUSION_BLASTER_H