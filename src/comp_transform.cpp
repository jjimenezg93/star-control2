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
	if (msg.m_type == EMT_GET_POS) {
		SGetPosMsg &getPosMsg = reinterpret_cast<SGetPosMsg &>(msg);
		getPosMsg.SetPos(m_x, m_y);
	} else if (msg.m_type == EMT_GET_ROT) {
		SGetRotMsg &rotMsg = reinterpret_cast<SGetRotMsg &>(msg);
		rotMsg.SetRot(m_rotation);
	} else if (msg.m_type == EMT_UPDATE_POS) {
		SUpdatePosMsg &moveMsg = reinterpret_cast<SUpdatePosMsg &>(msg);
		m_x += moveMsg.m_offsetX;
		m_y += moveMsg.m_offsetY;
	} else if (msg.m_type == EMT_UPDATE_ROT) {
		SUpdateRotMsg &rotMsg = reinterpret_cast<SUpdateRotMsg &>(msg);
		m_rotation += rotMsg.m_offsetRot;
	} else if (msg.m_type == EMT_SET_POS) {
		SSetPosMsg &posMsg = reinterpret_cast<SSetPosMsg &>(msg);
		m_x = posMsg.m_x;
		m_y = posMsg.m_y;
	} else if (msg.m_type == EMT_SET_ROT) {
		SSetRotMsg &rotMsg = reinterpret_cast<SSetRotMsg &>(msg);
		m_rotation = rotMsg.m_rot;
	}
}

void CCompTransform::Update(float elapsed) {

}

void CCompTransform::Render() {

}

