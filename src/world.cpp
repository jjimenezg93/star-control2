#include "../include/app_state.h"
#include "../include/component_collision.h"
#include "../include/component_playercontrol.h"
#include "../include/component_position.h"
#include "../include/component_render.h"
#include "../include/entities_factory.h"
#include "../include/entity.h"
#include "../include/defs.h"
#include "../include/entity_params.h"
#include "../include/image.h"
#include "../include/messages.h"
#include "../include/resourcemanager.h"
#include "../include/scene.h"
#include "../include/world.h"
#include "../include/screen.h"

#define BACKGROUND_IMG "data/game_background.jpg"

double genRandomF(double min, double max);

//std::vector<SEntityParams> g_entitiesParams;

CWorld::~CWorld() {
	ResourceManager::Instance().FreeResources();
}

uint8 CWorld::Init() {
	uint8 ret = 0;

	m_entitiesFactory.Init(*this); //should parse entities file and add them to this world

	CEntity * entity = m_entitiesFactory.SpawnEntity(SEntityParams(String("dreadnought"), true,
		EGameSide::EGS_PLAYER_1));

	AddEntity(entity, true);

	//after initializing the world, g_entitiesParams must be cleared in order to allow new games
	//to work properly
	g_entitiesParams.clear();

	return ret;
}

void CWorld::Update() {
	std::vector<CEntity *>::iterator itr = m_entities.begin();
	while (itr != m_entities.end()) {
		(*itr)->Update(static_cast<float>(Screen::Instance().ElapsedTime()));
		itr++;
	}
}

void CWorld::Render() {
	for (std::vector<CEntity *>::reverse_iterator itr = m_renderingEntities.rbegin();
	itr != m_renderingEntities.rend(); itr++) {
		(*itr)->Render();
	}
}

void CWorld::AddEntity(CEntity * et, bool render) {
	m_entities.push_back(et);
	if (render) {
		m_renderingEntities.push_back(et);
	}
}