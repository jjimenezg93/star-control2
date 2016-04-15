#ifndef _COMP_FUSION_BLASTER_H
#define _COMP_FUSION_BLASTER_H

#include "component.h"

class CCompFusionBlaster : public CComponent {
public:
	CCompFusionBlaster(CEntity * et, uint8 id);

	virtual void ReceiveMessage(SMessage &ev);
	virtual void Update(float elapsed);
	void Render();
private:
	uint8 m_id;
};

#endif //!_COMP_FUSION_BLASTER_H