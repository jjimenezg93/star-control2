#include <algorithm>

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
#define FINISH_TIME 2.5f

double genRandomF(double min, double max);
int8 g_winner;

CWorld::~CWorld() {
	for (std::vector<CEntity *>::iterator itr = m_entities.begin(); itr != m_entities.end();
	++itr) {
		DeleteEntity(*itr);
	}
	CleanVectors(); //must be called manually since it's normally called from Update()
}

uint8 CWorld::Init() {
	uint8 ret = 0;

	m_gameIsFinished = false;
	m_endTime = 0.f;

	m_entitiesFactory.Init(*this); //should parse entities file and add them to this world

	return ret;
}

void CWorld::GetPlayers(CEntity * &et1, CEntity * &et2) {
	std::vector<CEntity *>::iterator itr = m_entities.begin();
	et1 = nullptr;
	et2 = nullptr;
	while (itr != m_entities.end()) {
		if ((*itr)->GetType() == EET_SHIP && (*itr)->GetSide() == EGS_PLAYER_1)
			et1 = *itr;
		else if ((*itr)->GetType() == EET_SHIP && (*itr)->GetSide() == EGS_PLAYER_2)
			et2 = *itr;
		++itr;
	}
}
//returns pointer to the ship of the opposite side passed as parameter
CEntity * CWorld::GetEnemyShip(EGameSide side) const {
	std::vector<CEntity *>::const_iterator itr = m_entities.begin();
	while (itr != m_entities.end()) {
		if ((*itr)->GetType() == EET_SHIP && (*itr)->GetSide() != side)
			return *itr;
		++itr;
	}
	return nullptr;
}

void CWorld::Update() {
	if (m_gameIsFinished) {
		m_endTime += static_cast<float>(Screen::Instance().ElapsedTime());
	}
	if (m_endTime >= FINISH_TIME) {
		GSetWantedState(ESC_END_GAME);
	}
	std::vector<CEntity *>::iterator itr = m_entities.begin();
	while (itr != m_entities.end()) {
		(*itr)->Update(static_cast<float>(Screen::Instance().ElapsedTime()));
		itr++;
	}
	if (!m_gameIsFinished) {
		CheckCollisions();
	}
	CleanVectors();
}

void CWorld::CheckCollisions() {
	for (std::vector<CEntity *>::iterator itr = m_entities.begin(); itr != m_entities.end();
	++itr) {
		if ((*itr)->GetSide() == EGS_PLAYER_1) {
			for (std::vector<CEntity *>::iterator itOther = m_entities.begin();
			itOther != m_entities.end(); ++itOther) {
				if ((*itOther)->GetSide() == EGS_PLAYER_2) {
					(*itr)->IsCollision(*itOther);
				}
			}
		}
	}
}

void CWorld::CleanVectors() {
	uint8 shipsToDelete = 0; //if > 1 -> both ships were destroyed and there is no winner
	EGameSide shipDeleted = EGS_NONE;

	std::vector<CEntity *>::iterator itd = m_entitiesToDelete.begin();
	while (itd != m_entitiesToDelete.end()) {
		if ((*itd)->GetType() == EET_SHIP) {
			shipsToDelete++;
			shipDeleted = (*itd)->GetSide();
		}
		//render vector
		std::vector<CEntity *>::iterator renderItr = std::find(m_renderingEntities.begin(),
			m_renderingEntities.end(), *itd);
		if (renderItr != m_renderingEntities.end())
			m_renderingEntities.erase(renderItr);
		//update vector
		std::vector<CEntity *>::iterator itr = std::find(m_entities.begin(),
			m_entities.end(), *itd);
		if (itr != m_entities.end())
			m_entities.erase(itr);
		//toDelete vector
		delete *itd;
		itd = m_entitiesToDelete.erase(itd);
	}
	if (shipsToDelete == 1) {
		m_gameIsFinished = true;
		g_winner = static_cast<int8>(shipDeleted) - 1;
	} else if (shipsToDelete == 2) {
		m_gameIsFinished = true;
		g_winner = -1;
	}

	std::vector<CEntity *>::iterator ita = m_entitiesToAdd.begin();
	while (ita != m_entitiesToAdd.end()) {
		m_entities.push_back(*ita);
		if ((*ita)->IsRenderable()) {
			m_renderingEntities.push_back(*ita);
		}
		ita = m_entitiesToAdd.erase(ita);
	}
}

void CWorld::Render() {
	for (std::vector<CEntity *>::reverse_iterator itr = m_renderingEntities.rbegin();
	itr != m_renderingEntities.rend(); itr++) {
		(*itr)->Render();
	}
}

void CWorld::AddEntity(CEntity * const et) {
	m_entitiesToAdd.push_back(et);
}

void CWorld::DeleteEntity(CEntity * const et) {
	/*if (!m_gameIsFinished && et->GetType() == EET_SHIP) {
		m_gameIsFinished = true;
		g_winner = GetEnemyShip(et->GetSide())->GetSide() - 1;
	}*/
	m_entitiesToDelete.push_back(et);
}

void CWorld::ReceiveMessage(SMessage &msg) {
	for (std::vector<CEntity *>::iterator itr = m_entities.begin(); itr != m_entities.end();
	++itr) {
		(*itr)->ReceiveMessage(msg);
	}
}