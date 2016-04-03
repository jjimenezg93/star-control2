#ifndef _C_ENTITIES_FACTORY_H
#define _C_ENTITIES_FACTORY_H

#include "types.h"

#include <vector>

class CEntity;
enum EGameSide;

struct SEntityParams {
	SEntityParams(bool isAI, EGameSide side): m_isAI(isAI), m_side(side) {}
	bool m_isAI;
	EGameSide m_side;
};

class CEntitiesFactory {
public:
	uint8 Init();

	CEntity * SpawnEntity(SEntityParams params);

	void DeleteEntity(const CEntity * const entity);
private:

	//std::vector<CEntity> m_poolEntities;
};

#endif //!_C_ENTITIES_FACTORY_H