#ifndef _COMPONENT_H
#define _COMPONENT_H

class CEntity;
struct SMessage;

class CComponent {
public:
	virtual ~CComponent() {}

	virtual void ReceiveMessage(SMessage * const msg) = 0;
	virtual void Update(float elapsed) = 0;
protected:	
	CEntity * m_owner;
};

#endif //!_C_COMPONENT_H