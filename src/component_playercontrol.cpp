#include "../include/component_playercontrol.h"
#include "../include/component_position.h"
#include "../include/component_render.h"
#include "../include/entity.h"
#include "../../include/image.h"
#include "../include/messages.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"

CComponentPlayerControl::CComponentPlayerControl(CEntity * et) {
	m_owner = et;
}

void CComponentPlayerControl::ReceiveMessage(SMessage * msg) {
}

void CComponentPlayerControl::Update(float) {}