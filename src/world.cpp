#include "../include/app_state.h"
#include "../include/component_collision.h"
#include "../include/component_playercontrol.h"
#include "../include/component_position.h"
#include "../include/component_render.h"
#include "../include/entities_factory.h"
#include "../include/entity.h"
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

	m_entitiesFactory.Init();

	/*Image * avatar = ResourceManager::Instance().LoadImage("data/avatar/avatar_ship.png");
	avatar->SetMidHandle();
	m_entities.push_back(new CEntity(EGS_PLAYER_1));
	m_entities.push_back(new CEntity(EGS_PLAYER_2));
	Sprite * sprt = new Sprite(avatar);
	sprt->SetPosition(200, 200);
	Sprite * sprt2 = new Sprite(avatar);
	sprt2->SetPosition(500, 500);

	std::vector<CEntity *>::iterator itr = m_entities.begin();
	CComponentRender * renderComp = new CComponentRender(*itr, sprt);
	m_renderingEntities.push_back(*itr);
	(*itr++)->AddComponent(renderComp);
	CComponentRender * renderComp2 = new CComponentRender(*itr, sprt2);
	(*itr)->AddComponent(renderComp2);
	m_renderingEntities.push_back(*itr);*/

	return ret;
}

void CWorld::Update() {
	std::vector<CEntity *>::iterator itr = m_entities.begin();
	while (itr != m_entities.end()) {
		(*itr)->Update(Screen::Instance().ElapsedTime());
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