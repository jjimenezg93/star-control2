#ifndef _COMP_TRACTOR_DECOY_H
#define _COMP_TRACTOR_DECOY_H

#include "component.h"
#include "types.h"

class Image;

class CCompTractorDecoy: public CComponent {
public:
	CCompTractorDecoy(CEntity * const et, float decoyLifeTime);

	virtual void ReceiveMessage(SMessage &ev);
	virtual void Update(float elapsed);
	void Render();

private:
	float m_decoyLifeTime;
};

#endif //!_COMP_TRACTOR_DECOY_H