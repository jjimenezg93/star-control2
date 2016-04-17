#include "../include/app_state.h"
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

CWorld::~CWorld() {
	ResourceManager::Instance().FreeResources();
}

uint8 CWorld::Init() {
	uint8 ret = 0;

	m_entitiesFactory.Init(*this); //should parse entities file and add them to this world

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

void CWorld::AddEntity(CEntity * const et) {
	m_entities.push_back(et);
	if (et->IsRenderable()) {
		m_renderingEntities.push_back(et);
	}
}

void CWorld::DeleteEntity(CEntity * const et) {
	//when deleting -> problem in Entity::Update() after deleting components
	CEntity * etDelete = nullptr;
	std::vector<CEntity *>::iterator itr = m_entities.begin();
	while(itr != m_entities.end()) {
		if(et == *itr) {
			etDelete = *itr;
			m_entities.erase(itr);
			break;
		}
		++itr;
	}
	if(etDelete != nullptr) {
		delete etDelete;
	}
}