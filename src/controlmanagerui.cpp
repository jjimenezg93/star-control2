#include "../include/controlmanagerui.h"
#include "../include/controlui.h"
#include "../include/event.h"
#include "../include/ieventlistener.h"
#include "../include/inputmanager.h"

uint8 CControlManagerUI::Init() {
	uint8 ret = 0;
	// GUI receives only mouse events
	for (uint16 mouseId = 0; mouseId < EMouseEventID::EME_COUNT; ++mouseId) {
		CInputManager::Instance().Register(this, EEC_MOUSE, EMouseEventID(mouseId));
	}
	return ret;
}

void CControlManagerUI::Notify(const CEvent * const ev) {
	std::vector<CControlUI *>::reverse_iterator itr = m_controls.rbegin();
	while(itr != m_controls.rend()) {
		if ((*itr++)->ManageEvent(ev)) {
			if (ev->GetId() != EME_MOUSE_MOVED && ev->GetController() == EEC_MOUSE)
				//without this conditions, only 1 button displays properly after moving mouse out
				break;
		}
	}
}

void CControlManagerUI::AddControl(CControlUI * const control) {
	m_controls.push_back(control);
}

bool CControlManagerUI::RemoveControl(CControlUI * const control) {
	bool ret = false;
	std::vector<CControlUI *>::iterator itr = m_controls.begin();
	while (itr != m_controls.end()) {
		if ((*itr) == control) {
			itr = m_controls.erase(itr);
			ret = true;
			break;
		}
	}
	return ret;
}

void CControlManagerUI::Update() {
	for (std::vector<CControlUI *>::iterator itr = m_controls.begin();
	itr != m_controls.end(); ++itr) {
		(*itr)->Update();
	}
}

void CControlManagerUI::Render() {
	for (std::vector<CControlUI *>::iterator itr = m_controls.begin();
	itr != m_controls.end(); ++itr) {
		(*itr)->Render();
	}
}