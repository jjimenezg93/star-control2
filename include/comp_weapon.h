#ifndef _COMP_WEAPON_H
#define _COMP_WEAPON_H

#include <string>

#include "component.h"
#include "types.h"

class CEntity;
class Image;
struct SMessage;

class CCompWeapon: public CComponent {
public:
protected:
	CCompWeapon(CEntity * et, Image * img, uint8 id, uint16 energyConsumed, float cooldown):
		CComponent(et), m_projImg(img), m_id(id),
		m_energyConsumed(energyConsumed), m_cooldown(cooldown) {}

	void SetId(uint8 id) { m_id = id; }

	uint8 GetId() const { return m_id; }
	Image * GetImg() const { return m_projImg; }
	uint16 GetEnergyConsumed() const { return m_energyConsumed; }
	float GetCooldown() const { return m_cooldown; }
private:
	uint8 m_id;
	uint16 m_energyConsumed;
	float m_cooldown;
	Image * m_projImg;
};

#endif //!_COMP_WEAPON_H