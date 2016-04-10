#include <iostream>

#include "../include/component_shipparams.h"
#include "../include/component_render.h"
#include "../include/defs.h"
#include "../include/entities_factory.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#pragma warning(disable: 4512 4244) //encodedstream.h warning
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/filereadstream.h"
#pragma warning(default: 4512 4244)
#include "../include/world.h"

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

	const rapidjson::Value &ship = m_doc[params.m_shipName.c_str()];
	const rapidjson::Value &parameters = ship.FindMember("parameters")->value;

	//ship params
	float linearSpeed = parameters["linearSpeed"].GetFloat();
	float angularSpeed = parameters["angularSpeed"].GetFloat();
	int16 energy = static_cast<int16>(parameters["energy"].GetInt());
	int16 hitpoints = static_cast<int16>(parameters["hitpoints"].GetInt());
	
	entity->AddComponent(new CComponentShipParams(entity, linearSpeed, angularSpeed,
		energy, hitpoints));

	//components
	const rapidjson::Value &components = ship.FindMember("components")->value;

	for (rapidjson::Value::ConstMemberIterator itr = components.MemberBegin();
	itr != components.MemberEnd(); ++itr) {
		CComponent * newComp = CreateComponent(entity, itr);
		if (newComp != nullptr) { //provisional, while not all comps implemented
			entity->AddComponent(newComp);
		}
	}
}

CComponent * CEntitiesFactory::CreateComponent(CEntity * const et,
rapidjson::Value::ConstMemberIterator &compIt) {
	CComponent * comp = nullptr;
	std::string str = compIt->name.GetString();
	if (str == "render") {
		CComponentRender * renderComp = new CComponentRender(et,
			compIt->value["image"].GetString());
		comp = renderComp;
	}
	return comp;
}