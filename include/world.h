#ifndef _C_WORLD_H
#define _C_WORLD_H

#include "entities_factory.h"
#include "types.h"

#include <vector>

class CEntity;
class Player;
class Scene;

class CWorld {
public:
	CWorld() {} //needed for ASGame default constructor
	~CWorld();

	uint8 Init();

	void Update();
	void Render();

	void AddEntity(CEntity * et, bool render);
private:
	std::vector<CEntity *> m_entities;
	std::vector<CEntity *> m_renderingEntities;

	CEntitiesFactory m_entitiesFactory;
};

#endif //!_C_WORLD_H