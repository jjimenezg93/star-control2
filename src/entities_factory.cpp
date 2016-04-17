#include <iostream>

#include "../include/comp_collision.h"
#include "../include/comp_fusionblaster.h"
#include "../include/comp_playercontrol.h"
#include "../include/comp_projectilemove.h"
#include "../include/comp_render.h"
#include "../include/comp_shipparams.h"
#include "../include/comp_transform.h"
#include "../include/defs.h"
#include "../include/entities_factory.h"
#include "../include/entity.h"
#include "../include/event.h"
#include "../include/entity_params.h"
#include "../include/inputmanager.h"
#include "../include/image.h"
#include "../include/messages.h"
#include "../include/nsinputmanagerentity.h"
#include "../include/resourcemanager.h"
#pragma warning(disable: 4512 4244) //encodedstream.h warning
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/filereadstream.h"
#pragma warning(default: 4512 4244)
#include "../include/sprite.h"
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

	m_world = nullptr;

	return ret;
}

uint8 CEntitiesFactory::Init(CWorld &world) {
	uint8 ret = 0;
	
	Init();

	m_world = &world;

	for (std::vector<SEntityParams *>::iterator itr = g_entitiesParams.begin();
	itr != g_entitiesParams.end(); ++itr) {
		CEntity * et = SpawnEntity(*itr);
		world.AddEntity(et);
	}

	return ret;
}

CEntity * CEntitiesFactory::SpawnEntity(const SEntityParams * params) {
	CEntity * et = new CEntity(params->GetSide(), m_world);
	if(params->GetType() == EET_SHIP) {
		InitEntityControls(et);
		AddComponents(et, params);

		/* LOOKING INSIDE init_world.json and setting position/rotation */
		CCompTransform * transform = new CCompTransform(et, 0, 0, 0);
		et->AddComponent(transform); //will be set when init_world.json is parsed

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
	} else if(params->GetType() == EET_PROJECTILE) {
		AddComponents(et, params);
	}

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
//need to differentiate between ships and projectiles
void CEntitiesFactory::AddComponents(CEntity * const entity, const SEntityParams * params) {
	if(params->GetType() == EET_SHIP) {
		/* JSON COMPONENTS */
		const rapidjson::Value &ship = m_doc[static_cast<const SShipParams *>(params)->GetShipName().c_str()];
		const rapidjson::Value &parameters = ship.FindMember("parameters")->value;

		//ship params
		uint16 linearSpeed = static_cast<uint16>(parameters["linearSpeed"].GetInt());
		uint16 angularSpeed = static_cast<uint16>(parameters["angularSpeed"].GetInt());
		float energy = static_cast<float>(parameters["energy"].GetFloat());
		int16 hitpoints = static_cast<int16>(parameters["hitpoints"].GetInt());
	
		entity->AddComponent(new CCompShipParams(entity, linearSpeed, angularSpeed,
			energy, hitpoints));

		//components
		const rapidjson::Value &components = ship.FindMember("components")->value;

		for (rapidjson::Value::ConstMemberIterator itr = components.MemberBegin();
		itr != components.MemberEnd(); ++itr) {
			if (!strcmp(itr->name.GetString(), "ai") && !static_cast<const SShipParams *>(params)->IsAI()) {
				continue; //WHEN TESTING, DON'T USE AI
			} else if(!strcmp(itr->name.GetString(), "primaryWeapon")) {
				CComponent * comp = CreateWeapon(entity, 0, itr);
				entity->AddComponent(comp);
			} else if(!strcmp(itr->name.GetString(), "secondaryWeapon")) {
				CComponent * comp = CreateWeapon(entity, 1, itr);
				entity->AddComponent(comp);
			} else {
				CComponent * newComp = CreateComponent(entity, itr);
				entity->AddComponent(newComp);
			}
		}
	} else if(params->GetType() == EET_PROJECTILE) {
		const SProjectileParams * projParams = static_cast<const SProjectileParams *>(params);
		CCompTransform * transformComp = new CCompTransform(entity, 0, 0, 0);
		entity->AddComponent(transformComp);
		Sprite * sprt = new Sprite(projParams->GetImage());
		CCompRender * renderComp = new CCompRender(entity, sprt);
		entity->AddComponent(renderComp);
		SGetLinSpeedMsg getLinSpeedMsg;
		entity->ReceiveMessage(getLinSpeedMsg);
		SGetAngSpeedMsg getAngSpeedMsg;
		entity->ReceiveMessage(getAngSpeedMsg);
		CCompProjectileMove * projMoveComp = new CCompProjectileMove(entity,
			getLinSpeedMsg.GetLinSpeed(), getAngSpeedMsg.GetAngSpeed());
		entity->AddComponent(projMoveComp);

		SSetRotMsg setRotMsg(projParams->GetRot());
		entity->ReceiveMessage(setRotMsg);
		SSetPosMsg setPosMsg(projParams->GetX(), projParams->GetY());
		entity->ReceiveMessage(setPosMsg);
	}
	CCompCollision * colComp = new CCompCollision(entity);
	entity->AddComponent(colComp);
}

CComponent * CEntitiesFactory::CreateComponent(CEntity * const et,
rapidjson::Value::ConstMemberIterator &compIt) {
	CComponent * comp = nullptr;
	std::string str = compIt->name.GetString();
	if (!strcmp("render", compIt->name.GetString())) {
		CCompRender * renderComp = new CCompRender(et,
			compIt->value["image"].GetString());
		comp = renderComp;
	}
	return comp;
}

CComponent * CEntitiesFactory::CreateWeapon(CEntity * const et,
uint8 id, rapidjson::Value::ConstMemberIterator &compIt) {
	//parse weapon
	Image * img = ResourceManager::Instance().LoadImage(compIt->value["bulletImg"].GetString());
	float cooldown = static_cast<float>(compIt->value["cooldown"].GetFloat());
	uint16 energyConsumed = static_cast<uint16>(compIt->value["energyConsumed"].GetInt());
	CCompFusionBlaster * genComp = new CCompFusionBlaster(et,
		img, id, energyConsumed,
		cooldown);
	if(!strcmp("fusionBlaster", compIt->value["name"].GetString())) {
		Image * img = ResourceManager::Instance().LoadImage(compIt->value["bulletImg"].GetString());
		CCompFusionBlaster * fusionComp = new CCompFusionBlaster(et,
			img, id, static_cast<uint16>(compIt->value["energyConsumed"].GetInt()),
			static_cast<uint8>(compIt->value["cooldown"].GetInt()));
		return fusionComp;
	} else if(!strcmp("choppyBots", compIt->value["name"].GetString())) {
		Image * img = ResourceManager::Instance().LoadImage(compIt->value["bulletImg"].GetString());
		CCompFusionBlaster * fusionComp = new CCompFusionBlaster(et,
			img, id, static_cast<uint16>(compIt->value["energyConsumed"].GetInt()),
			static_cast<uint8>(compIt->value["cooldown"].GetInt()));
		return fusionComp;
	}
	return genComp;
}