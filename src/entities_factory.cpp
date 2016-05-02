#include <iostream>

#include "../include/comp_collision.h"
#include "../include/comp_explparams.h"
#include "../include/comp_fusionblaster.h"
#include "../include/comp_playercontrol.h"
#include "../include/comp_projectilemove.h"
#include "../include/comp_render.h"
#include "../include/comp_shipparams.h"
#include "../include/comp_projparams.h"
#include "../include/comp_transform.h"
#include "../include/comp_tractor_beam.h"
#include "../include/comp_tractor_decoy.h"
#include "../include/comp_decoyparams.h"
#include "../include/comp_choppythrower.h"
#include "../include/comp_botparams.h"
#include "../include/comp_ai_bot.h"
#include "../include/comp_ai_ship_default.h"
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
		//hotfix: create controls and register to InputManager if not AI
		AddComponents(et, params);
		//if (!static_cast<const SShipParams *>(params)->IsAI()) {
		InitEntityControls(et);

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
	} else if (params->GetType() == EET_EXPLOSION) {
		AddComponents(et, params);
	} else if (params->GetType() == EET_DECOY) {
		AddComponents(et, params);
	} else if (params->GetType() == EET_BOT) {
		AddComponents(et, params);
	}

	return et;
}

/*void CEntitiesFactory::DeleteEntity(const CEntity * const entity) {
	
}*/

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
		//CInputManager::Instance().Register(entity, EEC_KEYBOARD, itr->value.GetInt());
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
		const rapidjson::Value &ship = m_doc[static_cast<const SShipParams *>
			(params)->GetShipName().c_str()];
		const rapidjson::Value &parameters = ship.FindMember("parameters")->value;

		//ship params
		int16 linearSpeed = static_cast<int16>(parameters["linearSpeed"].GetInt());
		int16 angularSpeed = static_cast<int16>(parameters["angularSpeed"].GetInt());
		uint16 energy = static_cast<uint16>(parameters["energy"].GetInt());
		float energyChargeRate = static_cast<float>(parameters["energyChargeRate"].GetFloat());
		int16 hitpoints = static_cast<int16>(parameters["hitpoints"].GetInt());
		
		CCompShipParams * shipParamsComp = new CCompShipParams(entity, linearSpeed, angularSpeed,
			energy, energyChargeRate, hitpoints);
		entity->AddComponent(shipParamsComp);

		//components
		const rapidjson::Value &components = ship.FindMember("components")->value;

		for (rapidjson::Value::ConstMemberIterator itr = components.MemberBegin();
		itr != components.MemberEnd(); ++itr) {
			if (!strcmp(itr->name.GetString(), "ai")
			&& static_cast<const SShipParams *>(params)->IsAI()) {
				CComponent * comp = CreateAI(entity, itr->value["name"].GetString());
				entity->AddComponent(comp);
				//entity already has CCompShipParams, so set it's isAI to true
				SSetAIMsg setAIMsg(true);
				entity->ReceiveMessage(setAIMsg);
			} else if(!strcmp(itr->name.GetString(), "primaryWeapon")) {
				CComponent * comp = CreateWeapon(entity, 0, itr);
				entity->AddComponent(comp);
			} else if(!strcmp(itr->name.GetString(), "secondaryWeapon")) {
				CComponent * comp = CreateWeapon(entity, 1, itr);
				entity->AddComponent(comp);
			} else {
				CComponent * newComp = CreateComponent(entity, itr);
				if (newComp != nullptr) {
					entity->AddComponent(newComp);
				}
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

		CCompProjParams * projParamsComp = new CCompProjParams(entity, projParams->GetDamage());
		entity->AddComponent(projParamsComp);

		SSetRotMsg setRotMsg(projParams->GetRot());
		entity->ReceiveMessage(setRotMsg);
		SSetPosMsg setPosMsg(projParams->GetX(), projParams->GetY());
		entity->ReceiveMessage(setPosMsg);
	} else if (params->GetType() == EET_EXPLOSION) {
		const SExplosionParams * explParams = static_cast<const SExplosionParams *>(params);

		const rapidjson::Value &explosion = m_doc[static_cast<const SExplosionParams *>
			(params)->GetExplName().c_str()];

		//ship params
		Image * img = ResourceManager::Instance().LoadImage(explosion["image"].GetString(), 4, 4);
		img->SetMidHandle();
		float lifeTime = static_cast<float>(explosion["lifetime"].GetFloat());
		int16 fps = static_cast<int16>(explosion["fps"].GetInt());

		Sprite * sprt = new Sprite(img);
		sprt->SetFrameRange(0, 15);
		CCompRender * renderComp = new CCompRender(entity, sprt);
		entity->AddComponent(renderComp);

		entity->AddComponent(new CCompTransform(entity,
			explParams->GetX(), explParams->GetY(), explParams->GetRot()));

		entity->AddComponent(new CCompExplParams(entity, fps, lifeTime));

		SSetRotMsg setRotMsg(explParams->GetRot());
		entity->ReceiveMessage(setRotMsg);
		SSetPosMsg setPosMsg(explParams->GetX(), explParams->GetY());
		entity->ReceiveMessage(setPosMsg);
		SSetFPSMsg setFPSMsg(fps);
		entity->ReceiveMessage(setFPSMsg);
	} else if (params->GetType() == EET_DECOY) {
		const SDecoyParams * decoyParams = static_cast<const SDecoyParams *>(params);

		Sprite * sprt = new Sprite(decoyParams->GetImg());
		CCompRender * compRender = new CCompRender(entity, sprt);
		entity->AddComponent(compRender);

		CCompTransform * transfComp = new CCompTransform(entity, decoyParams->GetX(),
			decoyParams->GetY(), decoyParams->GetRot());
		entity->AddComponent(transfComp);

		CCompDecoyParams * decoyComp = new CCompDecoyParams(entity,	decoyParams->GetLifeTime(),
			decoyParams->GetDamage(), decoyParams->GetAttractFactor());
		entity->AddComponent(decoyComp);

		CCompTractorDecoy * tractorDecoyComp = new CCompTractorDecoy(entity,
			decoyParams->GetLifeTime());
		entity->AddComponent(tractorDecoyComp);

		SSetRotMsg setRotMsg(decoyParams->GetRot());
		entity->ReceiveMessage(setRotMsg);
		SSetPosMsg setPosMsg(decoyParams->GetX(), decoyParams->GetY());
		entity->ReceiveMessage(setPosMsg);
	} else if (params->GetType() == EET_BOT) {
		const SBotParams * botParams = static_cast<const SBotParams *>(params);

		Sprite * sprt = new Sprite(botParams->GetImg());
		CCompRender * compRender = new CCompRender(entity, sprt);
		entity->AddComponent(compRender);
		SSetFPSMsg setFpsMsg(20);
		compRender->ReceiveMessage(setFpsMsg);

		CCompTransform * transfComp = new CCompTransform(entity, botParams->GetX(),
			botParams->GetY(), 0.f);
		entity->AddComponent(transfComp);

		CCompBotParams * botParamsComp = new CCompBotParams(entity,
			botParams->GetLifeTime(), botParams->GetDamage(), botParams->GetSpeed());
		entity->AddComponent(botParamsComp);

		CCompAIBot * botAIComp = new CCompAIBot(entity, botParams->GetLifeTime());
		entity->AddComponent(botAIComp);

		SSetRotMsg setRotMsg(0.f);
		entity->ReceiveMessage(setRotMsg);
		SSetPosMsg setPosMsg(botParams->GetX(), botParams->GetY());
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
	if(!strcmp("fusionBlaster", compIt->value["name"].GetString())) {
		Image * img = ResourceManager::Instance().LoadImage(compIt->value["bulletImg"].GetString());
		CCompFusionBlaster * fusionBlasterComp = new CCompFusionBlaster(et,
			img, id, static_cast<float>(compIt->value["energyConsumed"].GetInt()),
			static_cast<float>(compIt->value["cooldown"].GetFloat()),
			static_cast<uint16>(compIt->value["damage"].GetInt()));
		return fusionBlasterComp;
	} else if(!strcmp("tractorBeam", compIt->value["name"].GetString())) {
		Image * img = ResourceManager::Instance().LoadImage(compIt->value["bulletImg"].GetString());
		CCompTractorBeam * tractorComp = new CCompTractorBeam(et,
			img, id, static_cast<float>(compIt->value["energyConsumed"].GetInt()),
			static_cast<float>(compIt->value["lifetime"].GetFloat()),
			static_cast<float>(compIt->value["cooldown"].GetFloat()),
			static_cast<uint16>(compIt->value["damage"].GetInt()),
			static_cast<float>(compIt->value["attractFactor"].GetFloat()));
		return tractorComp;
	} else if (!strcmp("choppyThrower", compIt->value["name"].GetString())) {
		Image * img = ResourceManager::Instance().LoadImage(
			compIt->value["bulletImg"].GetString(), 8, 8);
		CCompChoppyThrower * choppyComp = new CCompChoppyThrower(et,
			img, id, static_cast<float>(compIt->value["energyConsumed"].GetInt()),
			static_cast<float>(compIt->value["lifetime"].GetFloat()),
			static_cast<float>(compIt->value["cooldown"].GetFloat()),
			static_cast<uint16>(compIt->value["damage"].GetInt()),
			static_cast<float>(compIt->value["speed"].GetFloat()));
		return choppyComp;
	} else return nullptr;
}

CComponent * CEntitiesFactory::CreateAI(CEntity * const et, const char * name) {
	if (!strcmp(name, "defaultAI")) {
		CCompAIShipDefault * aiShip = new CCompAIShipDefault(et);
		return aiShip;
	}
	return nullptr;
}
