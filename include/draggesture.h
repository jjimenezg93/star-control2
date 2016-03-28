#ifndef _C_DRAG_GESTURE_H
#define _C_DRAG_GESTURE_H

#include "igesture.h"

template <typename T> class Array;
class CEvent;

class CDragGesture: public IGesture {
public:
	CDragGesture();

	virtual void ModifyArray(Array<CEvent *> &ev, const uint32 numEvents);
private:
	bool m_pressed;
	int32 m_x, m_y;
};

#endif //!_C_DRAG_GESTURE_H