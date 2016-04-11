#include <iostream>

#include "../include/entity.h"
#include "../include/defs.h"
#include "../include/event.h"
#include "../include/world.h"
#include "../include/component.h"
#include "../include/comp_render.h"
#include "../include/messages.h"

CEntity::CEntity(EGameSide side, bool renderable):
	m_side(side), m_renderable(renderable) {}

CEntity::~CEntity() {
	for (std::vector<CComponent *>::iterator it = m_components.begin();
	it != m_components.end(); it++) {
		delete *it;
	}
	m_components.clear();
}

void CEntity::AddComponent(CComponent * const comp) {
	m_components.insert(m_components.end(), comp);
	if (comp->GetType() == EComponent::EC_RENDER) {
		m_renderable = true;
	}
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

void CEntity::Render() {
	if (m_renderable) {
		reinterpret_cast<CCompRender *>(GetComponent(EC_RENDER))->Render();
	}
}

CComponent * CEntity::GetComponent(EComponent comp) const {
	std::vector<CComponent *>::const_iterator it = m_components.begin();
	while (it != m_components.end()) {
		if ((*it)->GetType() == comp) {
			return (*it);
		}
		it++;
	}
	return nullptr;
}

void CEntity::SetControls(uint16 controls[ENTITY_NUM_CONTROLS]) {
	memcpy(m_controls, controls, sizeof(m_controls));
}

void CEntity::Notify(const CEvent * const ev) {
	std::cout << m_side << " received " << ev->GetId() << std::endl;
}