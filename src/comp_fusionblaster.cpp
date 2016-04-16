#include <iostream>
#include "../include/comp_fusionblaster.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/image.h"
#include "../include/entities_factory.h"
#include "../include/messages.h"
#include "../include/world.h"

CCompFusionBlaster::CCompFusionBlaster(CEntity * et, Image * img,
	uint8 id, uint16 energyConsumed, float cooldown): CCompWeapon(et, img, id,
	energyConsumed, cooldown) {
	SetType(EC_FUSION_BLASTER);
}

void CCompFusionBlaster::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_SHOOT) {
		SShootMsg &shootMsg = static_cast<SShootMsg &>(msg);
		if(shootMsg.GetWeaponId() == GetId()) {
			std::cout << "weapon " << GetId() << " SHOOT!" << std::endl;
			SGetWorldMsg worldMsg;
			m_owner->ReceiveMessage(worldMsg);
			CWorld * world = worldMsg.GetWorld();
			//spawn projectile
			SGetRotMsg rotMsg;
			m_owner->ReceiveMessage(rotMsg);
			SGetPosMsg posMsg;
			m_owner->ReceiveMessage(posMsg);
			if(rotMsg.Modified()) {
				world->AddEntity(world->GetEntitiesFactory().SpawnEntity(new SProjectileParams(posMsg.GetX(), posMsg.GetY(),
					20, rotMsg.GetAngle(), m_owner->GetSide(), GetImg())));
			}
		}
	}
}

void CCompFusionBlaster::Update(float elapsed) {}

void CCompFusionBlaster::Render() {}
