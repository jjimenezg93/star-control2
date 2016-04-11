#ifndef _C_KEYBOARD_CONTROLLER_H
#define _C_KEYBOARD_CONTROLLER_H

#include <vector>

#include "types.h"

class CKeyboardController {
public:
	CKeyboardController();
	~CKeyboardController();
	uint8 Init();

	void Update();
private:
	void SendEvent(const uint32 id);

	int32 m_mouseX;
	int32 m_mouseY;

	std::vector<uint16> m_specialKeys;
};

#endif //!_C_KEYBOARD_CONTROLLER_H