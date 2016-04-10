#include "../include/component_shipparams.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"

CComponentShipParams::CComponentShipParams(CEntity * et, float linear, float angular,
int16 energy, int16 hitpoints):
m_linearSpeed(linear), m_angularSpeed(angular), m_energy(energy), m_hitpoints(hitpoints) {	
	m_owner = et;
}

void CComponentShipParams::ReceiveMessage(SMessage * msg) {

}

void CComponentShipParams::Update(float elapsed) {
	
}

void CComponentShipParams::Render() {
	
}