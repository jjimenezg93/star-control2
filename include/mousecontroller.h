#ifndef _C_MOUSE_CONTROLLER_H
#define _C_MOUSE_CONTROLLER_H

#include "types.h"

class CMouseController {
public:
	CMouseController();
	~CMouseController();
	uint8 Init();
	
	void Update();
private:
	void SendEvent(const uint32 id);
	
	int32 m_mouseX, m_mouseY, m_prevX, m_prevY;
};

#endif //!_C_MOUSE_CONTROLLER_H