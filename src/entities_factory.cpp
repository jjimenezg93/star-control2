#include <iostream>

#include "../include/comp_shipparams.h"
#include "../include/comp_render.h"
#include "../include/comp_playercontrol.h"
#include "../include/comp_transform.h"
#include "../include/defs.h"
#include "../include/entities_factory.h"
#include "../include/entity.h"
#include "../include/event.h"
#include "../include/entity_params.h"
#include "../include/inputmanager.h"
#include "../include/messages.h"
#include "../include/nsinputmanagerentity.h"
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
	
	InitEntityControls(et);
	AddComponents(et, params);

	/* LOOKING INSIDE init_world.json and setting position/rotation */
	FILE * wFile = fopen("data/conf/init_world.json", "rb");
	char buffer[65536];
	assert(wFile != nullptr && "CEntitiesFactory::SpawnEntity()");
	rapidjson::FileReadStream is(wFile, buffer, sizeof(buffer));
	rapidjson::Document cDoc;
	cDoc.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);
	assert(!cDoc.HasParseError());

	rapidjson::Value player;
	if (et->GetSide() == EGS_PLAYER_1) {
		player = cDoc["player1"];
	} else if (et->GetSide() == EGS_PLAYER_2) {
		player = cDoc["player2"];
	}

	for (rapidjson::Value::ConstMemberIterator itr = player.MemberBegin();
	itr != player.MemberEnd(); ++itr) {
		if (!strcmp(itr->name.GetString(), "position")) {
			SSetPosMsg posMsg(itr->value["x"].GetFloat(), itr->value["y"].GetFloat());
			et->ReceiveMessage(posMsg);
		} else if (!strcmp(itr->name.GetString(), "rotation")) {
			SSetRotMsg rotMsg(itr->value.GetFloat());
			et->ReceiveMessage(rotMsg);
		}
	}
	fclose(wFile);

	return et;
}

void CEntitiesFactory::DeleteEntity(const CEntity * const entity) {
	
}

void CEntitiesFactory::InitEntityControls(CEntity * const entity) {
	//controls
	FILE * cFile = fopen("data/conf/controls.json", "rb");
	char buffer[65536];
	assert(cFile != nullptr && "CEntitiesFactory::InitEntityControls()");
	rapidjson::FileReadStream is(cFile, buffer, sizeof(buffer));
	rapidjson::Document cDoc;
	cDoc.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);
	assert(!cDoc.HasParseError());

	rapidjson::Value player;
	if (entity->GetSide() == EGS_PLAYER_1) {
		player = cDoc["player1"].FindMember("controls")->value;
	} else if (entity->GetSide() == EGS_PLAYER_2) {
		player = cDoc["player2"].FindMember("controls")->value;
	}

	uint16 controls[kEntityNumControls];
	uint8 cont = 0;
	for (rapidjson::Value::ConstMemberIterator itr = player.MemberBegin();
	itr != player.MemberEnd(); ++itr) {
		uint16 value = static_cast<uint16>(itr->value.GetInt());
		memcpy(&controls[cont++], &value, sizeof(controls[0]));
		CInputManager::Instance().Register(entity, EEC_KEYBOARD, itr->value.GetInt());
	}

	CCompPlayerControl * playerControl = new CCompPlayerControl(entity);
	playerControl->SetControls(controls);

	entity->AddComponent(playerControl);

	fclose(cFile);
}

void CEntitiesFactory::AddComponents(CEntity * const entity, const SEntityParams &params) {
	
	
	/* JSON COMPONENTS */
	const rapidjson::Value &ship = m_doc[params.m_shipName.c_str()];
	const rapidjson::Value &parameters = ship.FindMember("parameters")->value;

	//ship params
	float linearSpeed = parameters["linearSpeed"].GetFloat();
	float angularSpeed = parameters["angularSpeed"].GetFloat();
	int16 energy = static_cast<int16>(parameters["energy"].GetInt());
	int16 hitpoints = static_cast<int16>(parameters["hitpoints"].GetInt());
	
	entity->AddComponent(new CCompShipParams(entity, linearSpeed, angularSpeed,
		energy, hitpoints));

	//components
	const rapidjson::Value &components = ship.FindMember("components")->value;

	for (rapidjson::Value::ConstMemberIterator itr = components.MemberBegin();
	itr != components.MemberEnd(); ++itr) {
		if (strcmp(itr->name.GetString(), "ai") && !params.m_isAI) {
			continue;
		}
		std::cout << "compName = " << itr->name.GetString() << std::endl;
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
		CCompRender * renderComp = new CCompRender(et,
			compIt->value["image"].GetString());
		comp = renderComp;
	}
	return comp;
}