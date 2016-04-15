#include "../include/comp_fusionblaster.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../include/world.h"

CCompFusionBlaster::CCompFusionBlaster(CEntity * et, uint8 id): CComponent(et) {
	SetType(EC_FUSION_BLASTER);
}

void CCompFusionBlaster::ReceiveMessage(SMessage &msg) {
	if (msg.m_type == EMT_SHOOT) {
		SShootMsg &shootMsg = static_cast<SShootMsg &>(msg);
		if(shootMsg.GetWeaponId() == m_id) {

		}
	}
}

void CCompFusionBlaster::Update(float elapsed) {
	SGetRotMsg rotMsg;
	m_owner->ReceiveMessage(rotMsg);
	float angle = 0.f;
	if(rotMsg.Modified())
		angle = rotMsg.GetAngle();

	SGetPosMsg posMsg;
	m_owner->ReceiveMessage(posMsg);
	float x = 0.f, y = 0.f;
	if(posMsg.Modified()) {
		x = posMsg.GetX();
		y = posMsg.GetY();
	}

	SGetWorldMsg worldMsg;
	m_owner->ReceiveMessage(worldMsg);
	CWorld * world = worldMsg.GetWorld();
	//access EntityFactory and spawn Projectile

}

void CCompFusionBlaster::Render() {

}
