#include "../include/component_render.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"
#include "../../include/resourcemanager.h"

CComponentRender::CComponentRender(CEntity * et, Sprite * sprt) {
	m_owner = et;
	m_sprite = sprt;
	SetType(EC_RENDER);
}


CComponentRender::CComponentRender(CEntity * et, const char * imgFilename) {
	m_owner = et;
	SetType(EC_RENDER);
	Image * img = ResourceManager::Instance().LoadImage(imgFilename);
	m_sprite = new Sprite(img);
}

void CComponentRender::ReceiveMessage(SMessage * msg) {
	
}

void CComponentRender::Update(float elapsed) {
	m_sprite->Update(elapsed);
}

void CComponentRender::Render() {
	m_sprite->Render();
}