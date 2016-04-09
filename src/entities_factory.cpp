#include "../include/component.h"
#include "../include/defs.h"
#include "../include/entities_factory.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#pragma warning(disable: 4512 4244) //encodedstream.h warning
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/filereadstream.h"
#include "../include/rapidjson/reader.h"
#pragma warning(default: 4512 4244)
#include "../include/world.h"
#include <iostream>

CEntitiesFactory::~CEntitiesFactory() {
	fclose(m_eFile);
}

uint8 CEntitiesFactory::Init() {
	uint8 ret = 0;

	m_eFile = fopen("data/conf/entities.json", "rb");
	char buffer[65536];
	assert(m_eFile != nullptr && "CEntitiesFactory::Init()");
	rapidjson::FileReadStream is(m_eFile, buffer, sizeof(buffer));
	m_doc.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);
	ret = m_doc.HasParseError();

	return ret;
}

uint8 CEntitiesFactory::Init(CWorld &world) {
	uint8 ret = 0;
	
	Init();

	for (std::vector<SEntityParams>::iterator itr = g_entitiesParams.begin();
	itr != g_entitiesParams.end(); ++itr) {
		CEntity * et = SpawnEntity(*itr);
		world.AddEntity(et);
	}

	return ret;
}

CEntity * CEntitiesFactory::SpawnEntity(const SEntityParams &params) {
	CEntity * et = new CEntity(params.m_side);

	AddComponents(et, params);

	return et;
}

void CEntitiesFactory::DeleteEntity(const CEntity * const entity) {
	
}

void CEntitiesFactory::AddComponents(CEntity * const entity, const SEntityParams &params) {
	//search for "components" in json -> create component -> entity.AddComponent(x)

	const rapidjson::Value &ship = m_doc[params.m_shipName.ToCString()];
	const rapidjson::Value::ConstMemberIterator &parameters = ship.FindMember("parameters");
	float linearSpeed = parameters->value["linearSpeed"].GetFloat();
	//String str = parameters->value["image"].GetString();

	/*const rapidjson::Value &dreadnought = m_doc["dreadnought"];

	//components loop
	for (rapidjson::Value::ConstMemberIterator itr = dreadnought.MemberBegin();
	itr != dreadnought.MemberEnd(); ++itr) {
		std::cout << "name : " << itr->name.GetString() << std::endl;
	}*/
}