#include "../include/entity.h"
#include "../include/defs.h"
#include "../include/world.h"
#include "../include/component.h"
#include "../include/messages.h"

CEntity::CEntity(EGameSide side): m_side(side) {}

CEntity::~CEntity() {
	for (std::vector<CComponent *>::iterator it = m_components.begin();
	it != m_components.end(); it++) {
		delete *it;
	}
	m_components.clear();
}

void CEntity::AddComponent(CComponent * const comp) {
	m_components.insert(m_components.end(), comp);
}

void CEntity::ReceiveMessage(SMessage * const msg) {
	for (std::vector<CComponent *>::iterator it = m_components.begin();
			it != m_components.end(); it++) {
		(*it)->ReceiveMessage(msg);
	}
}

void CEntity::Update(float elapsed) {
	for (std::vector<CComponent *>::iterator it = m_components.begin();
			it != m_components.end(); it++) {
		(*it)->Update(elapsed);
	}
}