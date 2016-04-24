#ifndef _COMPONENT_RENDER_H
#define _COMPONENT_RENDER_H

#include "component.h"
#include "types.h"

class Sprite;
struct SMessage;

class CCompRender: public CComponent {
public:
	CCompRender(CEntity * et, Sprite * sprt);
	CCompRender(CEntity * et, const char * imgFilename, uint16 h = 1, uint16 v = 1);

	Sprite * GetSprite() const { return m_sprite; }

	virtual void ReceiveMessage(SMessage &msg);
	virtual void Update(float elapsed);
	void Render();
private:
	Sprite * m_sprite;
};

#endif //!_COMPONENT_RENDER_H