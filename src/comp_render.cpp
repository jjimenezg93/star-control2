#include "../include/comp_render.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"
#include "../../include/resourcemanager.h"

CCompRender::CCompRender(CEntity * et, Sprite * sprt) {
	m_owner = et;
	m_sprite = sprt;
	SetType(EC_RENDER);
}


CCompRender::CCompRender(CEntity * et, const char * imgFilename) {
	m_owner = et;
	SetType(EC_RENDER);
	Image * img = ResourceManager::Instance().LoadImage(imgFilename);
	m_sprite = new Sprite(img);
}

void CCompRender::ReceiveMessage(SMessage * msg) {
	
}

void CCompRender::Update(float elapsed) {
	m_sprite->Update(elapsed);
}

void CCompRender::Render() {
	m_sprite->Render();
}