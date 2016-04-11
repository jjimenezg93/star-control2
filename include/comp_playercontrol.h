#ifndef _COMP_PLAYER_CONTROL_H
#define _COMP_PLAYER_CONTROL_H

#include "component.h"

class CCompPlayerControl: public CComponent {
public:
	CCompPlayerControl(CEntity * et);

	virtual void ReceiveMessage(SMessage * const msg);
	virtual void Update(float elapsed);
	void Render();
private:
};

#endif //!_COMP_PLAYER_CONTROL_H