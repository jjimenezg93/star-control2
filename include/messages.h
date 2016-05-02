#ifndef _MESSAGES_H
#define _MESSAGES_H

#include "types.h"

class CWorld;
enum EEventController;
enum EGameSide;
enum EEntityType;

enum EMessageType {
	EMT_INPUT,
	EMT_AI_INPUT,
	EMT_GET_WORLD,
	EMT_SET_POS,
	EMT_SET_ROT,
	EMT_GET_POS,
	EMT_GET_ROT,
	EMT_UPDATE_POS,
	EMT_UPDATE_ROT,
	EMT_GET_HP,
	EMT_UPDATE_HP,
	EMT_GET_ENERGY,
	EMT_UPDATE_ENERGY,
	EMT_GET_LINEAR_SPEED,
	EMT_GET_ANGULAR_SPEED,
	EMT_SHOOT,
	EMT_IS_COLLISION,
	EMT_GET_DAMAGE,
	EMT_GET_ENTITY_TYPE,
	EMT_SET_FPS,
	EMT_GET_ATTRACT_FACTOR,
	EMT_SET_AI,
	EMT_GET_AI
};

enum EAIInput {
	EAII_UP,
	EAII_DOWN,
	EAII_RIGHT,
	EAII_LEFT,
	EAII_SHOOT_PRIMARY,
	EAII_SHOOT_SECONDARY
};

struct SMessage {
	SMessage(EMessageType type): m_type(type) {}
	virtual ~SMessage() {}
	EMessageType m_type;
};
//raw input from InputManager
struct SInputMsg: public SMessage {
	SInputMsg(EEventController controller, uint32 id): SMessage(EMT_INPUT),
		m_controller(controller), m_id(id) {}
	EEventController GetController() const { return m_controller; }
	uint32 GetId() const { return m_id; }
private:
	EEventController m_controller;
	uint32 m_id;
};
//input from AI (hotfix)
struct SAIInputMsg: public SMessage {
	SAIInputMsg(EAIInput input): SMessage(EMT_AI_INPUT), m_input(input) {}
	EAIInput GetInput() const { return m_input; }
private:
	EAIInput m_input;
};

struct SGetWorldMsg: public SMessage {
	SGetWorldMsg(): SMessage(EMT_GET_WORLD), m_world(nullptr), m_modified(false) {}
	void SetWorld(CWorld * world) {
		if(!m_modified) {
			m_world = world;
			m_modified = true;
		}
	}
	CWorld * GetWorld() const { return m_world; }
	bool Modified() const { return m_modified; }
private:
	bool m_modified;
	CWorld * m_world;
};

struct SSetPosMsg: public SMessage {
	SSetPosMsg(float x, float y): SMessage(EMT_SET_POS),
		m_x(x), m_y(y) {
	}
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
private:
	float m_x, m_y;
};

struct SGetPosMsg: public SMessage {
	SGetPosMsg(): SMessage(EMT_GET_POS), m_x(0), m_y(0), m_modified(false) {}
	void SetPos(float x, float y) { m_x = x; m_y = y; m_modified = true; }
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
	bool Modified() { return m_modified; }
private:
	float m_x, m_y;
	bool m_modified;
};

struct SUpdatePosMsg: public SMessage {
	SUpdatePosMsg(float offsetX, float offsetY): SMessage(EMT_UPDATE_POS),
		m_offsetX(offsetX), m_offsetY(offsetY) {
	}
	float GetOffX() const { return m_offsetX; }
	float GetOffY() const { return m_offsetY; }
private:
	float m_offsetX, m_offsetY;
};

struct SSetRotMsg: public SMessage {
	SSetRotMsg(float rot): SMessage(EMT_SET_ROT),
		m_rot(rot) {
	}
	float GetRot() const { return m_rot; }
private:
	float m_rot;
};

struct SGetRotMsg: public SMessage {
	SGetRotMsg(): SMessage(EMT_GET_ROT), m_angle(0), m_modified(false) {}
	void SetRot(float angle) { m_angle = angle; m_modified = true; }
	float GetAngle() const { return m_angle; }
	bool Modified() { return m_modified; }
private:
	float m_angle;
	bool m_modified;
};

struct SUpdateRotMsg: public SMessage {
	SUpdateRotMsg(float offsetR): SMessage(EMT_UPDATE_ROT),
		m_offsetRot(offsetR) {
	}
	float GetOffRot() const { return m_offsetRot; }
private:
	float m_offsetRot;
};

struct SGetHitPointsMsg: public SMessage {
	SGetHitPointsMsg(): SMessage(EMT_GET_HP), m_hitPoints(0) {}
	void SetHitPoints(uint16 hp) {
		if (!m_modified) {
			m_hitPoints = hp;
			m_modified = true;
		}
	}
	uint16 GetHitPoints() const { return m_hitPoints; }
	bool Modified() { return m_modified; }
private:
	uint16 m_hitPoints;
	bool m_modified;
};

struct SUpdateHitPointsMsg: public SMessage {
	SUpdateHitPointsMsg(float dmg): SMessage(EMT_UPDATE_HP), m_damage(dmg) {}
	float GetDamage() const { return m_damage; }
private:
	float m_damage;
};

struct SGetEnergyMsg: public SMessage {
	SGetEnergyMsg(): SMessage(EMT_GET_ENERGY), m_energy(0) {}
	void SetEnergy(float en) {
		if (!m_modified) {
			m_energy = en;
			m_modified = true;
		}
	}
	float GetEnergy() const { return m_energy; }
	bool Modified() { return m_modified; }
private:
	float m_energy;
	bool m_modified;
};

struct SUpdateEnergyMsg: public SMessage {
	SUpdateEnergyMsg(float energy): SMessage(EMT_UPDATE_ENERGY), m_energy(energy) {}
	float GetEnergy() const { return m_energy; }
private:
	float m_energy;
};

struct SGetLinSpeedMsg: public SMessage {
	SGetLinSpeedMsg(): SMessage(EMT_GET_LINEAR_SPEED), m_linSpeed(0), m_modified(false) {}
	void SetLinSpeed(float lSpeed) { m_linSpeed = lSpeed; m_modified = true; }
	float GetLinSpeed() const { return m_linSpeed; }
	bool Modified() { return m_modified; }
private:
	float m_linSpeed;
	bool m_modified;
};

struct SGetAngSpeedMsg: public SMessage {
	SGetAngSpeedMsg(): SMessage(EMT_GET_ANGULAR_SPEED), m_angSpeed(0), m_modified(false) {}
	void SetAngSpeed(float aSpeed) { m_angSpeed = aSpeed; m_modified = true; }
	float GetAngSpeed() const { return m_angSpeed; }
	bool Modified() { return m_modified; }
private:
	float m_angSpeed;
	bool m_modified;
};

struct SShootMsg: public SMessage {
	SShootMsg(uint8 id) : SMessage(EMT_SHOOT), m_weaponId(id) {}
	uint8 GetWeaponId() const { return m_weaponId; }
private:
	uint8 m_weaponId;
};

struct SIsCollisionMsg: public SMessage {
	SIsCollisionMsg(CEntity * other): SMessage(EMT_IS_COLLISION),
		m_other(other), m_isCollision(false), m_modified(false) {}
	void SetIsCollision(bool isCol) {
		if (!m_modified) {
			m_isCollision = isCol;
			m_modified = true;
		}
	}
	CEntity * GetOther() const { return m_other; }
	bool GetIsCollision() const { return m_isCollision; }
	bool Modified() const { return m_modified; }
private:
	CEntity * m_other;
	bool m_isCollision;
	bool m_modified;
};

struct SGetDamageMsg: public SMessage {
	SGetDamageMsg(): SMessage(EMT_GET_DAMAGE), m_damage(0), m_modified(false) {}
	void SetDamage(float f) {
		if (!m_modified) {
			m_damage = f;
			m_modified = true;
		}
	}
	float GetDamage() const { return m_damage; }
	bool Modified() const { return m_modified; }
private:
	float m_damage;
	bool m_modified;
};

struct SGetEntityTypeMsg: public SMessage {
	SGetEntityTypeMsg(): SMessage(EMT_GET_ENTITY_TYPE), m_modified(false) {}
	void SetType(EEntityType type) {
		if (!m_modified) {
			m_type = type;
			m_modified = true;
		}
	}
	bool Modified() const { return m_modified; }
	EEntityType GetType() const { return m_type; }
private:
	bool m_modified;
	EEntityType m_type;
};

struct SSetFPSMsg: public SMessage {
	SSetFPSMsg(int16 fps): SMessage(EMT_SET_FPS), m_fps(fps) {}
	int16 GetFPS() const { return m_fps; }
private:
	int16 m_fps;
};

struct SGetAttractFactorMsg: public SMessage {
	SGetAttractFactorMsg(): SMessage(EMT_GET_ATTRACT_FACTOR), m_factor(0), m_modified(false) {}
	void SetAttractFactor(float f) {
		if (!m_modified) {
			m_factor = f;
			m_modified = true;
		}
	}
	float GetFactor() const { return m_factor; }
	bool Modified() const { return m_modified; }
private:
	float m_factor;
	bool m_modified;
};

struct SSetAIMsg: public SMessage {
	SSetAIMsg(bool isAI): SMessage(EMT_SET_AI), m_isAI(isAI) {}
	bool IsAI() const { return m_isAI; }
private:
	bool m_isAI;
};

struct SGetAIMsg: public SMessage {
	SGetAIMsg(): SMessage(EMT_GET_AI), m_modified(false), m_isAI(false) {}
	void SetIsAI(bool isAI) {
		if (!m_modified) {
			m_isAI = isAI;
			m_modified = true;
		}
	}
	bool IsAI() const { return m_isAI; }
	bool Modified() const { return m_modified; }
private:
	bool m_isAI, m_modified;
};

#endif //!_MESSAGES_H