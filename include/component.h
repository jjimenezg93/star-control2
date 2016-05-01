#ifndef _COMPONENT_H
#define _COMPONENT_H

class CEntity;
class CEvent;
struct SMessage;

enum EComponent {
	EC_SHIP_PARAMS,
	EC_PROJ_PARAMS,
	EC_EXPL_PARAMS,
	EC_DECOY_PARAMS,
	EC_BOT_PARAMS,
	EC_PLAYER_CONTROL,
	EC_RENDER,
	EC_TRANSFORM,
	EC_COLLISION,
	EC_FUSION_BLASTER,
	EC_TRACTOR_BEAM,
	EC_COMP_TRACTOR_DECOY,
	EC_CHOPPY_THROWER,
	EC_COMP_CHOPPY_BOT,
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