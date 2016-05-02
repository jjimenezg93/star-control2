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
	m_sprite->SetCollision(Sprite::CollisionMode::COLLISION_CIRCLE);
}


CCompRender::CCompRender(CEntity * et, const char * imgFilename, uint16 h, uint16 v):
CComponent(et) {
	SetType(EC_RENDER);
	Image * img = ResourceManager::Instance().LoadImage(imgFilename, h, v);
	img->SetMidHandle();
	m_sprite = new Sprite(img);
	m_sprite->SetCollision(Sprite::CollisionMode::COLLISION_CIRCLE);
}

void CCompRender::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_SET_POS) {
		SSetPosMsg &posMsg = reinterpret_cast<SSetPosMsg &>(msg);
		m_sprite->SetPosition(posMsg.GetX(), posMsg.GetY());
	} else if (msg.m_type == EMT_SET_ROT) {
		SSetRotMsg &rotMsg = reinterpret_cast<SSetRotMsg &>(msg);
		m_sprite->SetAngle(rotMsg.GetRot());
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