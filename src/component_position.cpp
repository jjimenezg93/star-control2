#include "../include/component_position.h"
#include "../include/component_render.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../../include/screen.h"

CComponentPosition::CComponentPosition(CEntity * et, float x, float y) {
	m_owner = et;
	m_x = x;
	m_y = y;
}

void CComponentPosition::ReceiveMessage(SMessage * msg) {
}

void CComponentPosition::Update(float) {
}