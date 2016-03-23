#include "../include/as_start_menu.h"
#include "../include/buttonui.h"
#include "../include/defs.h"
#include "../include/inputmanager.h"
#include "../include/menu_defs.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/screen.h"

#include <iostream>

ASStartMenu::~ASStartMenu() {

}

void ASStartMenu::Init() {
	Image * defaultImg = ResourceManager::Instance().LoadImage(BUTTON_DEFAULT_IMG);
	Image * onclickImg = ResourceManager::Instance().LoadImage(BUTTON_ONCLICK_IMG);
	Image * inactiveImg = ResourceManager::Instance().LoadImage(BUTTON_INACTIVE_IMG);

	m_controlManager.Init();

	CButtonUI * exitButton = new CButtonUI();
	exitButton->Init(500, 500, defaultImg, onclickImg, inactiveImg);
	exitButton->SetId(1);
	exitButton->AddEventListener(this);
	m_menuControls.push_back(exitButton);
	
	m_controlManager.AddControl(exitButton);
}

void ASStartMenu::Deactivate() {
}

void ASStartMenu::ProcessInput() {
	CInputManager::Instance().Update();
}

void ASStartMenu::Update() {	
	m_controlManager.Update();
}

void ASStartMenu::Draw() {
	Renderer::Instance().Clear();
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	std::vector<CControlUI *>::reverse_iterator itrControls;
	for (itrControls = m_menuControls.rbegin(); itrControls != m_menuControls.rend();
	++itrControls) {
		(*itrControls)->Render();
	}

	Screen::Instance().Refresh();
}

void ASStartMenu::ManageControlEvent(CControlUI * const sender) {
	switch (sender->GetType()) {
	case ECT_BUTTON:
		if (sender->GetId() == 1) {
			GSetWantedState(ESC_EXIT_APP);
		}
		break;
	default:
		break;
	}
}