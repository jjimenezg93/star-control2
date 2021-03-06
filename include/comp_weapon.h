#ifndef _COMP_WEAPON_H
#define _COMP_WEAPON_H

#include <string>

#include "component.h"
#include "types.h"

class CEntity;
class Image;
struct SMessage;

class CCompWeapon: public CComponent {
protected:
	CCompWeapon(CEntity * et, Image * img, uint8 id,
		float energyConsumed, float cooldown, uint16 damage):
		CComponent(et), m_projImg(img), m_id(id),
		m_energyConsumed(energyConsumed), m_cooldown(cooldown), m_damage(damage) {
		SetType(EC_FUSION_BLASTER);
	}

	void SetId(uint8 id) { m_id = id; }

	uint8 GetId() const { return m_id; }
	Image * GetImg() const { return m_projImg; }
	float GetEnergyConsumed() const { return m_energyConsumed; }
	uint16 GetDamage() const { return m_damage; }
	float GetCooldown() const { return m_cooldown; }

	float m_lastShot;
private:
	uint8 m_id;
	uint16 m_damage;
	float m_cooldown, m_energyConsumed;
	Image * m_projImg;
};

#endif //!_COMP_WEAPON_H