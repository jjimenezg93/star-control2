#include "../include/comp_shipparams.h"
#include "../include/entity.h"
#include "../include/event.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"

CCompShipParams::CCompShipParams(CEntity * et, float linear, float angular,
int16 energy, int16 hitpoints):
	CComponent(et), m_linearSpeed(linear), m_angularSpeed(angular),
	m_energy(energy), m_hitpoints(hitpoints) {}

void CCompShipParams::ReceiveMessage(SMessage &msg) {

}

void CCompShipParams::Update(float elapsed) {
	
}

void CCompShipParams::Render() {
	
}