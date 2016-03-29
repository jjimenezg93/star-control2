#include "../include/clickgesture.h"
#include "../include/controlmanagerui.h"
#include "../include/draggesture.h"
#include "../include/event.h"
#include "../include/inputmanager.h"
#include "../include/iregistrable.h"
#include "../include/keyboardcontroller.h"
#include "../include/mousecontroller.h"

CInputManager * CInputManager::inputmanager = nullptr;

CInputManager &CInputManager::Instance() {
	if (!inputmanager) {
		inputmanager = new CInputManager();
		if (inputmanager->Init()) {
			delete inputmanager;
			inputmanager = nullptr;
		}
	}
	return *inputmanager;
}

CInputManager::IMObserver::IMObserver(IRegistrable * const ob, const EEventController e,
const uint32 id) {
	m_observer = ob;
	m_controller = e;
	m_id = id;
}

CInputManager::CInputManager() {}

uint8 CInputManager::Init() {
	uint8 ret = 0;

	m_keyboardController = new CKeyboardController();
	if (m_keyboardController->Init()) {
		ret = 1;
	}

	m_mouseController = new CMouseController();
	if (m_mouseController->Init()) {
		ret = 1;
	}

	m_gestureManagers.Add(new CClickGesture());
	m_gestureManagers.Add(new CDragGesture());

	return ret;
}

CInputManager::~CInputManager() {
	for (uint32 i = 0; i < m_observers.Size(); i++) {
		delete m_observers[i];
	}
}

uint8 CInputManager::Register(IRegistrable * const obj, const EEventController controller,
const uint32 eventId) {
	uint8 ret = 0;
	uint32 i = 0;
	bool alreadyIn = false;
	while (i < m_observers.Size()) { //inefficient -> sort array (binary search)
		if (m_observers[i]->m_observer == obj && m_observers[i]->m_controller == controller
		&& m_observers[i]->m_id == eventId) {
			alreadyIn = true;
			break;
		}
		i++;
	}

	if (!alreadyIn)
		m_observers.Add(new IMObserver(obj, controller, eventId));
	else ret = 1;

	return ret;
}

uint8 CInputManager::Unregister(IRegistrable * const obj, const EEventController controller,
		const uint32 eventId) {
	uint8 ret = 1;
	uint32 i = 0;
	while (i < m_observers.Size()) { //inefficient -> sort array (binary search)
		if (m_observers[i]->m_observer == obj && m_observers[i]->m_controller == controller
				&& m_observers[i]->m_id == eventId) {    
			m_observers.RemoveAt(i);
			ret = 0;
		}
		i++;
	}
	return ret;
}

void CInputManager::Update() {
	m_keyboardController->Update();
	m_mouseController->Update();
	ProcessGestures();
	ManageEvents();
}

void CInputManager::ProcessGestures() {
	for (uint16 i = 0; i < m_gestureManagers.Size(); i++) {
		m_gestureManagers[i]->ModifyArray(m_events, m_events.Size());
	}
}

void CInputManager::ManageEvents() {
	for (uint32 i = 0; i < m_events.Size(); i++) {
		for (uint32 j = 0; j < m_observers.Size(); j++) {
			if (m_events[i]->GetController() == m_observers[j]->m_controller
				&& m_events[i]->GetId() == m_observers[j]->m_id) {
				m_observers[j]->m_observer->Notify(m_events[i]);
			}
		}
	}
	while (m_events.Size() > 0) {
		delete m_events[0];
		m_events.RemoveAt(0);
	}
}

void CInputManager::AddEvent(CEvent * const ev) {
	m_events.Add(ev);
}