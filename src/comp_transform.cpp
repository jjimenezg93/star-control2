#include "../include/comp_transform.h"
#include "../include/event.h"
#include "../include/messages.h"

CCompTransform::CCompTransform(CEntity * et): CComponent(et) {
	SetType(EC_TRANSFORM);
}

CCompTransform::CCompTransform(CEntity * et, float x, float y):
CComponent(et), m_x(x), m_y(y) {
	SetType(EC_TRANSFORM);
}

void CCompTransform::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_UPDATE_POS) {
		SUpdatePosMessage &moveMsg = reinterpret_cast<SUpdatePosMessage &>(msg);
		m_x += moveMsg.m_offsetX;
		m_y += moveMsg.m_offsetY;
		//update Rendering position
	}
}

void CCompTransform::Update(float elapsed) {

}

void CCompTransform::Render() {

}

