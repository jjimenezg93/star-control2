#ifndef _C_ENTITIES_FACTORY_H
#define _C_ENTITIES_FACTORY_H

#include <string>
#include <vector>

#pragma warning(disable: 4512 4244) //encodedstream.h warning
#include "../include/rapidjson/document.h"
#pragma warning(default: 4512 4244)
#include "types.h"

class CComponent;
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

	//World is responsible of deallocating entities
	CEntity * SpawnEntity(const SEntityParams * params);

	//would be used if entities pool is implemented
	//void DeleteEntity(const CEntity * const entity);
private:
	void InitEntityControls(CEntity * const entity);
	void AddComponents(CEntity * const entity, const SEntityParams * params);
	CComponent * CreateComponent(CEntity * const et,
		rapidjson::Value::ConstMemberIterator &compIt);
	CComponent * CreateWeapon(CEntity * const et,
		uint8 id, rapidjson::Value::ConstMemberIterator &compIt);
	CComponent * CreateAI(CEntity * const et, const char * name);

	CWorld * m_world;

	FILE * m_eFile;
	rapidjson::Document m_doc;
	//std::vector<CEntity> m_poolEntities;
};

#endif //!_C_ENTITIES_FACTORY_H