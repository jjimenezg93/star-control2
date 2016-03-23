#ifndef _C_CLICK_GESTURE_H
#define _C_CLICK_GESTURE_H

#include "igesture.h"

#include <ctime>
#include <chrono>

template <typename T> class Array;
class CEvent;

class CClickGesture: public IGesture {
public:
	CClickGesture();

	virtual void ModifyArray(Array<CEvent *> &ev, const uint32 numEvents);
private:
	clock_t m_pressTime;
	clock_t m_releaseTime;

	bool m_pressed;
};

#endif //!_C_CLICK_GESTURE_H