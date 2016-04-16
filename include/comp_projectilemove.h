#ifndef _COMP_PROJECTILE_MOVE_H
#define _COMP_PROJECTILE_MOVE_H

#include "component.h"
#include "types.h"

class CCompProjectileMove: public CComponent {
public:
	~CCompProjectileMove();

	CCompProjectileMove(CEntity * et, float linSpeed, float angSpeed);

	virtual void ReceiveMessage(SMessage &ev) = 0;
	virtual void Update(float elapsed) = 0;
private:
	float m_linSpeed, m_angSpeed;
};

#endif //!_COMP_PROJECTILE_MOVE_H