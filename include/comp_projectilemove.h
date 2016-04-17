#ifndef _COMP_PROJECTILE_MOVE_H
#define _COMP_PROJECTILE_MOVE_H

#include "component.h"
#include "types.h"

class CCompProjectileMove: public CComponent {
public:
	~CCompProjectileMove();

	CCompProjectileMove(CEntity * et, float linSpeed, float angSpeed);

	virtual void ReceiveMessage(SMessage &ev);
	virtual void Update(float elapsed);
private:
	float m_linSpeed, m_angSpeed;
};

#endif //!_COMP_PROJECTILE_MOVE_H