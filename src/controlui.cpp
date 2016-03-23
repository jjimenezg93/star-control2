#include "../include/controlui.h"
#include "../include/event.h"
#include "../include/ieventlistener.h"

CControlUI::~CControlUI() {
	std::vector<CControlUI *>::iterator itr = m_controls.begin();
	while (itr != m_controls.end()) {
		itr = m_controls.erase(itr);
	}
	m_controls.clear();
	m_listeners.clear(); //mustn't delete listeners
}

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
			if (ev->GetId() != EME_MOUSE_MOVED && ev->GetController() == EEC_MOUSE)
				//without this conditions, only 1 button displays properly after moving mouse out
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
			break;
		}
		++itr;
	}
}

void CControlUI::AddControl(CControlUI * const control) {
	m_controls.push_back(control);
}

bool CControlUI::RemoveControl(CControlUI * const control) {
	bool ret = false;
	std::vector<CControlUI *>::iterator itr = m_controls.begin();
	while (itr != m_controls.end()) {
		if ((*itr) == control) {
			m_controls.erase(itr);
			ret = true;
			break;
		}
		++itr;
	}
	return ret;
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

const std::vector<CControlUI *> & CControlUI::GetControls() const {
	return m_controls;
}