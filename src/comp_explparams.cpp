#include "../include/comp_explparams.h"
#include "../include/image.h"
#include "../include/resourcemanager.h"

CCompExplParams::CCompExplParams(CEntity * et, int16 fps, float lifeTime):
CComponent(et), m_fps(fps), m_lifeTime(lifeTime) {
	m_currentTime = 0.f;
}

void CCompExplParams::ReceiveMessage(SMessage & msg) {
}

void CCompExplParams::Update(float elapsed) {
	m_currentTime += elapsed;
	if (m_currentTime >= m_lifeTime) {
		//message to destroy itself
	}
}

void CCompExplParams::Render() {
}
