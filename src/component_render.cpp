#include "../include/component_render.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"

CComponentRender::CComponentRender(CEntity * et, Sprite * sprt) {
	m_owner = et;
	m_sprite = sprt;
	SetType(EC_RENDER);
}

void CComponentRender::ReceiveMessage(SMessage * msg) {
	
}

void CComponentRender::Update(float elapsed) {
	if (!m_sprite->IsRotating()) m_sprite->RotateTo(
		static_cast<int32>(m_sprite->GetAngle()) - 180, 60.f);
	m_sprite->Update(elapsed);
}

void CComponentRender::Render() {
	m_sprite->Render();
}