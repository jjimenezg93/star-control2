#include <iostream>

#include "../include/audiobuffer.h"
#include "../include/audiosource.h"
#include "../include/comp_tractor_decoy.h"
#include "../include/entity.h"
#include "../include/entity_params.h"
#include "../include/image.h"
#include "../include/entities_factory.h"
#include "../include/messages.h"
#include "../include/world.h"

CCompTractorDecoy::CCompTractorDecoy(CEntity * et, float decoyLifeTime):
	CComponent(et), m_decoyLifeTime(decoyLifeTime) {
	SetType(EC_COMP_TRACTOR_DECOY);
}

void CCompTractorDecoy::ReceiveMessage(SMessage &msg) {
	
}

void CCompTractorDecoy::Update(float elapsed) {
	//must store a pointer to enemy ship in Constructor or by a message, and here it has to
	//send a message to attract it
}

void CCompTractorDecoy::Render() {}
