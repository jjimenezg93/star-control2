#ifndef _I_REGISTRABLE_H
#define _I_REGISTRABLE_H

class CEvent;

class IRegistrable {
public:
	virtual void Notify(const CEvent * const) {}
};

#endif //!_I_REGISTRABLE_H