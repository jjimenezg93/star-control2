#ifndef _I_GESTURE_H
#define _I_GESTURE_H

#include "types.h"

class CEvent;
template <typename T> class Array;

class IGesture {
public:
	virtual void ModifyArray(Array<CEvent *> &, const uint32) {}
};

#endif //!_I_GESTURE_H