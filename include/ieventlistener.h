#ifndef _I_EVENT_LISTENER_H
#define _I_EVENT_LISTENER_H

class CControlUI;

class IEventListener {
public:
	virtual void ManageControlEvent(CControlUI * const sender) = 0;
};

#endif //!_I_EVENT_LISTENER_H