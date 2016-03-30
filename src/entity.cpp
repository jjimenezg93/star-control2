#include "../include/entity.h"
#include "../include/defs.h"
#include "../include/world.h"
#include "../include/component.h"
#include "../include/messages.h"

CEntity::CEntity() {
}

CEntity::~CEntity() {}

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