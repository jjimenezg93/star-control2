#include "../include/as_game_conf_menu.h"
#include "../include/buttonui.h"
#include "../include/defs.h"
#include "../include/inputmanager.h"
#include "../include/image.h"
#include "../include/menu_defs.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/screen.h"
#include "../include/string.h"
#include "../include/windowui.h"

ASGameConfMenu::~ASGameConfMenu() {
	if (g_wantedState == ESC_EXIT_APP) {
		ResourceManager::Instance().FreeResources();
		for (std::vector<CControlUI *>::iterator itr = m_menuControls.begin();
		itr != m_menuControls.end(); ++itr) {
			m_controlManager.RemoveControl((*itr));
			delete (*itr);
		}
		m_menuControls.clear();
	}
}

void ASGameConfMenu::Init() {
	String str; //used to send all str's by reference, then copied inside

	Image * defaultButtonImg = ResourceManager::Instance().LoadImage(BUTTON_DEFAULT_IMG);
	defaultButtonImg->SetMidHandle();
	Image * onclickButtonImg = ResourceManager::Instance().LoadImage(BUTTON_ONCLICK_IMG);
	onclickButtonImg->SetMidHandle();
	Image * inactiveButtonImg = ResourceManager::Instance().LoadImage(BUTTON_INACTIVE_IMG);
	inactiveButtonImg->SetMidHandle();

	Image * windowImg = ResourceManager::Instance().LoadImage(WINDOW_IMG);
	windowImg->SetMidHandle();

	Image * backgroundImg = ResourceManager::Instance().LoadImage(MENU_BACKGROUND_IMG);

	uint16 screenWidth = Screen::Instance().GetWidth();
	uint16 screenHeight = Screen::Instance().GetHeight();

	m_controlManager.Init();
}

void ASGameConfMenu::ProcessInput() {
	CInputManager::Instance().Update();
}

void ASGameConfMenu::Update() {
	m_controlManager.Update();
}

void ASGameConfMenu::Draw() {
	Renderer::Instance().Clear();
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	m_controlManager.Render();

	Screen::Instance().Refresh();
}

void ASGameConfMenu::ManageControlEvent(CControlUI * const sender) {

}
