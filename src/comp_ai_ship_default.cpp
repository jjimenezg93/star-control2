#include "../include/comp_ai_ship_default.h"

CCompShipDefault::CCompShipDefault(CEntity * const et): CComponent(et) {

}

void CCompShipDefault::ReceiveMessage(SMessage & ev) {

}

void CCompShipDefault::Update(float elapsed) {
	m_lastDecision += elapsed;

	if (m_lastDecision >= m_nextDecision) {
		switch (m_currentState) {
		case ESS_MOVE:

			break;
		case ESS_AIM:

			break;
		case ESS_ATTACK:

			break;
		default:
			break;
		}
	}
}
