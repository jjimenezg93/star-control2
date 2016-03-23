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
	return ret;
}

void CKeyboardController::Update() {
	glfwGetMousePos(&m_mouseX, &m_mouseY);
	if (glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS) {
		SendEvent(EKE_SPACE);
	}
}

void CKeyboardController::SendEvent(const uint32 id) {
	CEvent * ev = new CEvent(EEC_KEYBOARD, id, m_mouseX, m_mouseY);
	IInputManagerController::AddEvent(ev);
}