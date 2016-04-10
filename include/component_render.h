#ifndef _COMPONENT_RENDER_H
#define _COMPONENT_RENDER_H

#include "component.h"

class Sprite;

class CComponentRender: public CComponent {
public:
	CComponentRender(CEntity * et, Sprite * sprt);
	CComponentRender(CEntity * et, const char * imgFilename);

	virtual void ReceiveMessage(SMessage * const msg);
	virtual void Update(float elapsed);
	void Render();
private:
	Sprite * m_sprite;
};

#endif //!_COMPONENT_RENDER_H