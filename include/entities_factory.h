#ifndef _C_ENTITIES_FACTORY_H
#define _C_ENTITIES_FACTORY_H

#include "types.h"
#include "string.h"

#include <vector>

class CEntity;
class CWorld;
enum EGameSide;
enum EComponent;
struct SEntityParams;

class CEntitiesFactory {
public:
	uint8 Init();
	uint8 Init(CWorld &world);

	CEntity * SpawnEntity(SEntityParams params);

	void DeleteEntity(const CEntity * const entity);

private:
	void AddComponents(CEntity * const entity);

	//std::vector<CEntity> m_poolEntities;
};

#endif //!_C_ENTITIES_FACTORY_H