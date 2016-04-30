#ifndef _COMPONENT_DECOY_PARAMS_H
#define _COMPONENT_DECOY_PARAMS_H

#include "component.h"
#include "types.h"

class CCompDecoyParams: public CComponent {
public:
	CCompDecoyParams(CEntity * et, float lifeTime, float damage);

	virtual void ReceiveMessage(SMessage &msg);
	virtual void Update(float elapsed);
	void Render();
private:
	int16 m_fps;
	float m_lifeTime;
	float m_damage;
	float m_currentTime;
};

#endif //!_COMPONENT_DECOY_PARAMS_H