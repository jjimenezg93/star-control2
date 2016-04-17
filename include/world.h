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

	void AddEntity(CEntity * const et);
	void DeleteEntity(CEntity * const et);

	CEntitiesFactory &GetEntitiesFactory() { return m_entitiesFactory; }
private:
	//this removes entities to delete from all World vectors
	void CleanVectors();

	std::vector<CEntity *> m_entities;
	std::vector<CEntity *> m_renderingEntities;
	std::vector<CEntity *> m_entitiesToDelete;

	CEntitiesFactory m_entitiesFactory;
};

#endif //!_C_WORLD_H