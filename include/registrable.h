#ifndef _I_REGISTRABLE_H
#define _I_REGISTRABLE_H

class CEvent;

class IRegistrable {
public:
	virtual void Notify(CEvent *) {}
	virtual void ManageEvent(CEvent *) {}
};

#endif //!_I_REGISTRABLE_H