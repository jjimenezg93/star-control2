#ifndef _COMPONENT_H
#define _COMPONENT_H

class CEntity;
class CEvent;
struct SMessage;

enum EComponent {
	EC_PLAYER_CONTROL,
	EC_RENDER,
	EC_TRANSFORM,
	EC_COLLISION,
	EC_FUSION_BLASTER,
	EC_PROJECTILE_MOVE
};

class CComponent {
public:
	virtual ~CComponent() {}

	EComponent GetType() const { return m_type; }

	virtual void ReceiveMessage(SMessage &ev) = 0;
	virtual void Update(float elapsed) = 0;
protected:
	CComponent(CEntity * et): m_owner(et) {}
	void SetType(EComponent newType) { m_type = newType; }
	CEntity * m_owner;

	EComponent m_type;
};

#endif //!_C_COMPONENT_H