#include "../include/component.h"
#include "../include/defs.h"
#include "../include/entities_factory.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#pragma warning(disable: 4512 4244) //encodedstream.h warning
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/filereadstream.h"
#pragma warning(default: 4512 4244)
#include "../include/world.h"
#include <iostream>

uint8 CEntitiesFactory::Init() {
	uint8 ret = 0;

	return ret;
}

uint8 CEntitiesFactory::Init(CWorld &world) {
	/*FILE* pFile = fopen("data/conf/entities.json", "rb");
	char buffer[65536];
	rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
	rapidjson::Document document;
	document.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);

	//need to empty g_entitiesParams before starting world again
	if (document.IsObject() && document.HasMember(g_entitiesParams.begin()->m_name.ToCString())) {
		std::cout << "Has dreadnought" << std::endl;
	}*/

	//CEntity * newEntity = SpawnEntity(paramms);
	//world.AddEntity(newEntity);
}

CEntity * CEntitiesFactory::SpawnEntity(SEntityParams params) {
	CEntity * et = new CEntity(params.m_side);

	AddComponents(et);

	return et;
}

void CEntitiesFactory::DeleteEntity(const CEntity * const entity) {
	
}

void CEntitiesFactory::AddComponents(CEntity * const entity) {
	//search for "components" in json -> create component -> entity.AddComponent(x)
}