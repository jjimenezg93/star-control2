#ifndef _COMP_TRANSFORM_H
#define _COMP_TRANSFORM_H

#include "component.h"

class CCompTransform: public CComponent {
public:
	CCompTransform(CEntity * et);
	CCompTransform(CEntity * et, float x, float y, float rot);

	virtual void ReceiveMessage(SMessage &ev);
	virtual void Update(float elapsed);
	void Render();
private:
	float m_x, m_y;
	float m_rotation;
};

#endif //!_COMP_TRANSFORM_H