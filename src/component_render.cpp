#include "../include/component_render.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"

CComponentRender::CComponentRender(CEntity * et, Sprite * sprt) {
	m_owner = et;
	m_sprite = sprt;
}

void CComponentRender::ReceiveMessage(SMessage * msg) {
	
}

void CComponentRender::Update(float) {
	
}