#ifndef _COMPONENT_BOT_PARAMS_H
#define _COMPONENT_BOT_PARAMS_H

#include "component.h"
#include "types.h"

class CCompBotParams: public CComponent {
public:
	CCompBotParams(CEntity * et, float lifeTime, float damage, float speed);

	virtual void ReceiveMessage(SMessage &msg);
	virtual void Update(float elapsed);
private:
	int16 m_fps;
	float m_lifeTime;
	float m_damage;
	float m_speed;
	float m_currentTime;
};

#endif //!_COMPONENT_BOT_PARAMS_H