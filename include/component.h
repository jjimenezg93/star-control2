#ifndef _COMPONENT_H
#define _COMPONENT_H

class CEntity;
struct SMessage;

enum EComponent {
	EC_RENDER
};

class CComponent {
public:

	virtual ~CComponent() {}

	EComponent GetType() const { return m_type; }

	virtual void ReceiveMessage(SMessage * const msg) = 0;
	virtual void Update(float elapsed) = 0;
protected:
	void SetType(EComponent newType) { m_type = newType; }
	CEntity * m_owner;

	EComponent m_type;
};

#endif //!_C_COMPONENT_H