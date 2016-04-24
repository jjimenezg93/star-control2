#ifndef _COMPONENT_EXPL_PARAMS_H
#define _COMPONENT_EXPL_PARAMS_H

#include "component.h"
#include "types.h"


class CCompExplParams: public CComponent {
public:
	CCompExplParams(CEntity * et, int16 fps, float lifeTime);

	virtual void ReceiveMessage(SMessage &msg);
	virtual void Update(float elapsed);
	void Render();
private:
	int16 m_fps;
	float m_lifeTime;
	float m_currentTime;
};

#endif //!_COMPONENT_EXPL_PARAMS_H