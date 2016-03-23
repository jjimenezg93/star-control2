#ifndef _C_EVENT_H
#define _C_EVENT_H

#include "types.h"

enum EEventController {
	EEC_MOUSE,
	EEC_KEYBOARD,
	EEC_PAD,
	EEC_COUNT //iterating
};

enum EMouseEventID {
	EME_MOUSE_MOVED,
	EME_LMB_PRESS,
	EME_LMB_RELEASE,
	EME_LMB_CLICK,
	EME_RMB_PRESS,
	EME_RMB_RELEASE,
	EME_COUNT //iterating
};

enum EKeyboardEventID {
	EKE_SPACE,
	EKE_COUNT //iterating
};

class CEvent {
public:
	CEvent(const EEventController controller, const uint32 id,
			const int32 x = 0, const int32 y = 0);

	EEventController GetController() const { return m_controller; }
	uint32 GetId() const { return m_id; }

	void SetId(const EMouseEventID newId) { m_id = newId; }
	
	int32 GetX() const { return m_x; }
	int32 GetY() const { return m_y; }
private:
	EEventController m_controller;
	uint32 m_id;
	int32 m_x, m_y;
};

#endif //!_C_EVENT_H