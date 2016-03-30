#pragma warning(disable: 4061)
//ET_NUM_COLORS not explicitly handled (GetImageByEntityType -> switch-case)

#include "../include/app_state.h"
#include "../include/component_collision.h"
#include "../include/component_playercontrol.h"
#include "../include/component_position.h"
#include "../include/component_render.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../include/world.h"

#include "../../include/u-gine.h"

double genRandomF(double min, double max);

CWorld::CWorld(const String background) {
	m_scene = new Scene(ResourceManager::Instance().LoadImage(background));

	m_player = nullptr;
}

CWorld::~CWorld() {
	ResourceManager::Instance().FreeResources();
	
}

void CWorld::Run() {
	
}

void CWorld::Draw() {
	m_scene->Render();
	Screen::Instance().Refresh();
}

void CWorld::DespawnEntity(unsigned int pos) {
	
}