#include "../include/comp_render.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"
#include "../../include/resourcemanager.h"

CCompRender::CCompRender(CEntity * et, Sprite * sprt): CComponent(et), m_sprite(sprt) {
	m_sprite = sprt;
	SetType(EC_RENDER);
	m_sprite->SetCollision(Sprite::CollisionMode::COLLISION_RECT);
}


CCompRender::CCompRender(CEntity * et, const char * imgFilename, uint16 h, uint16 v):
CComponent(et) {
	SetType(EC_RENDER);
	EEntityType type = et->GetType();
	Image * img = ResourceManager::Instance().LoadImage(imgFilename, h, v);
	img->SetMidHandle();
	m_sprite = new Sprite(img);
	m_sprite->SetCollision(Sprite::CollisionMode::COLLISION_RECT);
}

void CCompRender::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_UPDATE_POS) {
		SUpdatePosMsg &moveMsg = reinterpret_cast<SUpdatePosMsg &>(msg);
		m_sprite->SetPosition(m_sprite->GetX() + moveMsg.m_offsetX,
			m_sprite->GetY() + moveMsg.m_offsetY);
	} else if (msg.m_type == EMT_UPDATE_ROT) {
		SUpdateRotMsg &rotMsg = reinterpret_cast<SUpdateRotMsg &>(msg);
		m_sprite->SetAngle(m_sprite->GetAngle() + rotMsg.m_offsetRot);
	} else if (msg.m_type == EMT_SET_POS) {
		SSetPosMsg &posMsg = reinterpret_cast<SSetPosMsg &>(msg);
		m_sprite->SetPosition(posMsg.m_x, posMsg.m_y);
	} else if (msg.m_type == EMT_SET_ROT) {
		SSetRotMsg &rotMsg = reinterpret_cast<SSetRotMsg &>(msg);
		m_sprite->SetAngle(rotMsg.m_rot);
	} else if (msg.m_type == EMT_SET_FPS) {
		SSetFPSMsg &setFPSMsg = reinterpret_cast<SSetFPSMsg &>(msg);
		m_sprite->SetFPS(setFPSMsg.GetFPS());
	}
}

void CCompRender::Update(float elapsed) {
	m_sprite->Update(elapsed);
}

void CCompRender::Render() {
	m_sprite->Render();
}