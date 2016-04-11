#include "../include/event.h"
#include "../include/keyboardcontroller.h"
#include "../include/nsinputmanagercontroller.h"

#include "../lib/glfw.h"

CKeyboardController::CKeyboardController() {}

CKeyboardController::~CKeyboardController() {
	glfwTerminate();
}

uint8 CKeyboardController::Init() {
	uint8 ret = 0;
	if (!glfwInit()) {
		ret = 1;
	}

	m_specialKeys.push_back(GLFW_KEY_LEFT);
	m_specialKeys.push_back(GLFW_KEY_RIGHT);
	m_specialKeys.push_back(GLFW_KEY_UP);
	m_specialKeys.push_back(GLFW_KEY_DOWN);
	m_specialKeys.push_back(GLFW_KEY_ENTER);
	
	return ret;
}

void CKeyboardController::Update() {
	glfwGetMousePos(&m_mouseX, &m_mouseY);
	for (uint8 i = EKE_FIRST_CODE; i <= EKE_LAST_CODE; i++) {
		if (glfwGetKey(i) == GLFW_PRESS) {
			SendEvent(i);
		}
	}
	for (std::vector<uint16>::iterator it = m_specialKeys.begin(); it != m_specialKeys.end();
	++it) {
		if (glfwGetKey(*it) == GLFW_PRESS) {
			SendEvent(*it);
		}
	}
}

void CKeyboardController::SendEvent(const uint32 id) {
	CEvent * ev = new CEvent(EEC_KEYBOARD, id, m_mouseX, m_mouseY);
	IInputManagerController::AddEvent(ev);
}