#include "../include/component_collision.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../../include/sprite.h"

CComponentCollision::CComponentCollision(CEntity * et, Sprite * sprt) {
	m_owner = et;
	m_sprite = sprt;
}

void CComponentCollision::ReceiveMessage(SMessage * msg) {
}

void CComponentCollision::Update(float) {}