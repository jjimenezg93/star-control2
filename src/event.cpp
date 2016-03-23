#include "../include/event.h"

CEvent::CEvent(const EEventController controller, const uint32 id, const int32 x, const int32 y) {
	m_controller = controller;
	m_id = id;
	m_x = x;
	m_y = y;
}