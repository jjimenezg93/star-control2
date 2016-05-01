#ifndef _COMP_AI_BOT_H
#define _COMP_AI_BOT_H

#include "component.h"
#include "types.h"

class Image;

class CCompAIBot: public CComponent {
public:
	CCompAIBot(CEntity * const et, float lifeTime);

	virtual void ReceiveMessage(SMessage &ev);
	virtual void Update(float elapsed);

private:
	float m_lifeTime;
	CEntity * m_enemyShip;
};

#endif //!_COMP_AI_BOT_H