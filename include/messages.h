#ifndef _MESSAGES_H
#define _MESSAGES_H

#include "types.h"

class CWorld;
enum EEventController;
enum EGameSide;
enum EEntityType;

enum EMessageType {
	EMT_INPUT,
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
	EMT_GET_ENTITY_TYPE
};

struct SMessage {
	SMessage(EMessageType type): m_type(type) {}
	virtual ~SMessage() {}
	EMessageType m_type;
};

struct SInputMsg: public SMessage {
	SInputMsg(): SMessage(EMT_INPUT) {}
	SInputMsg(EEventController controller, uint32 id): SMessage(EMT_INPUT),
		m_controller(controller), m_id(id) {}
	EEventController m_controller;
	uint32 m_id;
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
	SSetPosMsg(): SMessage(EMT_SET_POS) {}
	SSetPosMsg(float x, float y): SMessage(EMT_SET_POS),
		m_x(x), m_y(y) {
	}
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
	SUpdatePosMsg(): SMessage(EMT_UPDATE_POS) {}
	SUpdatePosMsg(float offsetX, float offsetY): SMessage(EMT_UPDATE_POS),
		m_offsetX(offsetX), m_offsetY(offsetY) {
	}
	float m_offsetX, m_offsetY;
};

struct SSetRotMsg: public SMessage {
	SSetRotMsg(): SMessage(EMT_SET_ROT) {}
	SSetRotMsg(float rot): SMessage(EMT_SET_ROT),
		m_rot(rot) {
	}
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
	SUpdateRotMsg(): SMessage(EMT_UPDATE_ROT) {}
	SUpdateRotMsg(float offsetR): SMessage(EMT_UPDATE_ROT),
		m_offsetRot(offsetR) {
	}
	float m_offsetRot;
};

struct SGetHitPointsMsg: public SMessage {
	SGetHitPointsMsg(): SMessage(EMT_GET_HP), m_hitPoints(0) {}
	void SetHitPoints(uint16 hp) {
		m_hitPoints = hp;
		m_modified = true;
	}
	uint16 GetHitPoints() const { return m_hitPoints; }
	bool Modified() { return m_modified; }
private:
	uint16 m_hitPoints;
	bool m_modified;
};

struct SUpdateHitPointsMsg: public SMessage {
	SUpdateHitPointsMsg(int16 dmg = 0): SMessage(EMT_UPDATE_HP), m_damage(dmg) {}
	int16 m_damage;
};

struct SGetEnergyMsg: public SMessage {
	SGetEnergyMsg(): SMessage(EMT_GET_ENERGY), m_energy(0) {}
	void SetEnergy(uint16 en) {
		m_energy = en;
		m_modified = true;
	}
	uint16 GetEnergy() const { return m_energy; }
	bool Modified() { return m_modified; }
private:
	uint16 m_energy;
	bool m_modified;
};

struct SUpdateEnergyMsg: public SMessage {
	SUpdateEnergyMsg(uint16 energy = 0): SMessage(EMT_UPDATE_ENERGY), m_energy(energy) {}
	uint16 m_energy;
};

struct SGetLinSpeedMsg: public SMessage {
	SGetLinSpeedMsg(): SMessage(EMT_GET_LINEAR_SPEED), m_linSpeed(0), m_modified(false) {}
	void SetLinSpeed(int16 lSpeed) { m_linSpeed = lSpeed; m_modified = true; }
	int16 GetLinSpeed() const { return m_linSpeed; }
	bool Modified() { return m_modified; }
private:
	int16 m_linSpeed;
	bool m_modified;
};

struct SGetAngSpeedMsg: public SMessage {
	SGetAngSpeedMsg(): SMessage(EMT_GET_ANGULAR_SPEED), m_angSpeed(0), m_modified(false) {}
	void SetAngSpeed(int16 aSpeed) { m_angSpeed = aSpeed; m_modified = true; }
	int16 GetAngSpeed() const { return m_angSpeed; }
	bool Modified() { return m_modified; }
private:
	int16 m_angSpeed;
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
		m_isCollision = isCol;
		m_modified = true;
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
	void SetDamage(uint16 f) {
		if (!m_modified) {
			m_damage = f;
			m_modified = true;
		}
	}
	uint16 GetDamage() const { return m_damage; }
	bool Modified() const { return m_modified; }
private:
	uint16 m_damage;
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

#endif //!_MESSAGES_H