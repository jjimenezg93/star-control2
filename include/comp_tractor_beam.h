#ifndef _COMP_TRACTOR_BEAM_H
#define _COMP_TRACTOR_BEAM_H

#include "comp_weapon.h"
#include "types.h"

class Image;

class CCompTractorBeam: public CCompWeapon {
public:
	CCompTractorBeam(CEntity * const et, Image * img, uint8 id, uint16 energyConsumed,
		float lifeTime, float cooldown, uint16 damage, float attractFactor);

	virtual void ReceiveMessage(SMessage &ev);
	virtual void Update(float elapsed);
	void Render();
private:
	float m_decoyLifeTime;
	float m_attractFactor;
};

#endif //!_COMP_TRACTOR_BEAM_H