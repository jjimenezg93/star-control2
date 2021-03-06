#ifndef _S_ENTITY_PARAMS_H
#define _S_ENTITY_PARAMS_H

#include <string>

class Image;

enum EEntityType {
	EET_SHIP,
	EET_PROJECTILE,
	EET_DECOY,
	EET_BOT,
	EET_EXPLOSION
};

enum EGameSide {
	EGS_NONE,
	EGS_PLAYER_1,
	EGS_PLAYER_2,
	EGS_NEUTRAL
};

struct SEntityParams {
	virtual EEntityType GetType() const { return m_type; }
	virtual EGameSide GetSide() const { return m_side; }
protected:
	SEntityParams(EEntityType type, EGameSide side): m_type(type), m_side(side) {}
	EEntityType m_type;
	EGameSide m_side;
};

struct SShipParams: public SEntityParams {
	SShipParams(std::string shipName, bool isAI, EGameSide side):
		SEntityParams(EET_SHIP, side), m_shipName(shipName), m_isAI(isAI) {}
	const std::string & GetShipName() const { return m_shipName; }
	bool IsAI() const { return m_isAI; }
private:
	std::string m_shipName;
	bool m_isAI;
};

struct SProjectileParams: public SEntityParams {
	SProjectileParams(float x, float y, float linSpeed, float rot,
		EGameSide side, Image * img, uint16 damage):
		SEntityParams(EET_PROJECTILE, side), m_x(x), m_y(y),
		m_linSpeed(linSpeed), m_rot(rot), m_image(img), m_damage(damage) {}
	Image * GetImage() const { return m_image; }
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
	float GetLinSpeed() const { return m_linSpeed; }
	float GetRot() const { return m_rot; }
	uint16 GetDamage() const { return m_damage; }
private:
	Image * m_image;
	float m_x, m_y;
	float m_linSpeed;
	float m_rot;
	uint16 m_damage;
};

struct SDecoyParams: public SEntityParams {
	SDecoyParams(EGameSide side, Image * img, float x, float y,
		float rot, float lifeTime, uint16 damage, float attractFactor):
		SEntityParams(EET_DECOY, side),	m_image(img), m_x(x), m_y(y), m_rot(rot),
		m_lifeTime(lifeTime), m_damage(damage), m_attractFactor(attractFactor) {}

	Image * GetImg() const { return m_image; }
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
	float GetRot() const { return m_rot; }
	float GetLifeTime() const { return m_lifeTime; }
	uint16 GetDamage() const { return m_damage; }
	float GetAttractFactor() const { return m_attractFactor; }
private:
	Image * m_image;
	uint16 m_damage;
	float m_x, m_y, m_rot, m_lifeTime, m_attractFactor;
};

struct SBotParams: public SEntityParams {
	SBotParams(EGameSide side, Image * img, float x, float y,
		float lifeTime, uint16 damage, float speed):
		SEntityParams(EET_BOT, side), m_image(img), m_x(x),
		m_y(y), m_lifeTime(lifeTime), m_damage(damage), m_speed(speed) {
	}

	Image * GetImg() const { return m_image; }
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
	float GetLifeTime() const { return m_lifeTime; }
	float GetSpeed() const { return m_speed; }
	uint16 GetDamage() const { return m_damage; }
private:
	Image * m_image;
	uint16 m_damage;
	float m_x, m_y, m_speed, m_lifeTime;
};

struct SExplosionParams: public SEntityParams {
	SExplosionParams(std::string name, EGameSide side, float x, float y, float rot = 0.f):
		SEntityParams(EET_EXPLOSION, side), m_explName(name), m_x(x), m_y(y), m_rot(rot) {}
	const std::string & GetExplName() const { return m_explName; }
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
	float GetRot() const { return m_rot; }
private:
	std::string m_explName;
	float m_x, m_y, m_rot;
};

#endif //!_S_ENTITY_PARAMS_H