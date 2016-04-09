#ifndef _C_ENTITIES_FACTORY_H
#define _C_ENTITIES_FACTORY_H

#pragma warning(disable: 4512 4244) //encodedstream.h warning
#include "../include/rapidjson/document.h"
#pragma warning(default: 4512 4244)
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
	~CEntitiesFactory();

	uint8 Init();
	uint8 Init(CWorld &world);

	CEntity * SpawnEntity(const SEntityParams &params);

	void DeleteEntity(const CEntity * const entity);
private:
	void AddComponents(CEntity * const entity, const SEntityParams &params);

	FILE * m_eFile;
	rapidjson::Document m_doc;
	//std::vector<CEntity> m_poolEntities;
};

#endif //!_C_ENTITIES_FACTORY_H