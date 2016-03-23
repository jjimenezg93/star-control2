#include "../include/controlui.h"
#include "../include/event.h"
#include "../include/ieventlistener.h"

void CControlUI::Update() {
	for (std::vector<CControlUI *>::iterator itr = m_controls.begin();
	itr != m_controls.end(); ++itr) {
		(*itr)->Update();
	}
}

void CControlUI::Render() {
	for (std::vector<CControlUI *>::iterator itr = m_controls.begin();
	itr != m_controls.end(); ++itr) {
		(*itr)->Render();
	}
}

bool CControlUI::ManageEvent(const CEvent * const ev) {
	bool consumed = false;
	
	//using reverse_iterator so the latest control ("closer" in screen), consumes event first
	std::vector<CControlUI *>::reverse_iterator itr = m_controls.rbegin();
	while (itr != m_controls.rend()) {
		if ((*itr++)->ManageEvent(ev)) {
			consumed = true;
			break;
		}
	}

	return consumed;
}

void CControlUI::AddEventListener(IEventListener * const eventListener) {
	m_listeners.push_back(eventListener);
}

void CControlUI::RemoveEventListener(IEventListener * const eventListener) {
	std::vector<IEventListener *>::iterator itr = m_listeners.begin();
	while (itr != m_listeners.end()) {
		if ((*itr) == eventListener) {
			m_listeners.erase(itr);
		}
		++itr;
	}
}

void CControlUI::AddControl(CControlUI * const control) {
	m_controls.push_back(control);
}

void CControlUI::RemoveControl(CControlUI * const control) {
	std::vector<CControlUI *>::iterator itr = m_controls.begin();
	while (itr != m_controls.end()) {
		if ((*itr) == control) {
			m_controls.erase(itr);
		}
		++itr;
	}
}

CGUIRender & CControlUI::GetGUIRender() {
	return m_guirender;
}

void CControlUI::SetCurrentState(const EGUICurrentState newState) {
	m_currentState = newState;
}

void CControlUI::SetType(const EControlType type) {
	m_type = type;
}

void CControlUI::NotifyListeners(CControlUI * const sender) {
	for (std::vector<IEventListener *>::iterator itr = m_listeners.begin();
	itr != m_listeners.end(); ++itr) {
		(*itr)->ManageControlEvent(sender);
	}
}