#ifndef _S_ENTITY_PARAMS_H
#define _S_ENTITY_PARAMS_H

#include <string>

class Image;

enum EEntityType {
	EET_SHIP,
	EET_PROJECTILE
};

enum EGameSide {
	EGS_PLAYER_1,
	EGS_PLAYER_2
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
	SProjectileParams(float linSpeed, float rot, EGameSide side, Image * img):
		SEntityParams(EET_PROJECTILE, side), m_linSpeed(linSpeed), m_rot(rot), m_image(img) {}
	Image * GetImage() const { return m_image; }
	float GetLinSpeed() const { return m_linSpeed; }
	float GetRot() const { return m_rot; }
private:
	Image * m_image;
	float m_linSpeed;
	float m_rot;
};

#endif //!_S_ENTITY_PARAMS_H