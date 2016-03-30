#ifndef _COMPONENT_RENDER_H
#define _COMPONENT_RENDER_H

#include "component.h"

class Sprite;

class CComponentRender: public CComponent {
public:
	CComponentRender(CEntity * et, Sprite * sprt);

	virtual void ReceiveMessage(SMessage * const msg);
	virtual void Update(float elapsed);
private:
	Sprite * m_sprite;
};

#endif //!_COMPONENT_RENDER_H