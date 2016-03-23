#include "../include/as_start_menu.h"
#include "../include/buttonui.h"
#include "../include/defs.h"
#include "../include/inputmanager.h"
#include "../include/image.h"
#include "../include/menu_defs.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/screen.h"
#include "../include/string.h"

#include <iostream>

ASStartMenu::~ASStartMenu() {
	ResourceManager::Instance().FreeResources();
	for (std::vector<CControlUI *>::iterator itr = m_menuControls.begin();
	itr != m_menuControls.end(); ++itr) {
		m_controlManager.RemoveControl((*itr));
		delete (*itr);
	}
	m_menuControls.clear();
}

void ASStartMenu::Init() {
	String str; //used to send all str's by reference, then copied inside
	Image * defaultButtonImg = ResourceManager::Instance().LoadImage(BUTTON_DEFAULT_IMG);
	defaultButtonImg->SetMidHandle();
	Image * onclickButtonImg = ResourceManager::Instance().LoadImage(BUTTON_ONCLICK_IMG);
	onclickButtonImg->SetMidHandle();
	Image * inactiveButtonImg = ResourceManager::Instance().LoadImage(BUTTON_INACTIVE_IMG);
	inactiveButtonImg->SetMidHandle();

	m_controlManager.Init();

	uint16 screenWidth = Screen::Instance().GetWidth();
	uint16 screenHeight = Screen::Instance().GetHeight();

	CButtonUI * playButton = new CButtonUI();
	playButton->Init(screenWidth / 2, screenHeight / 2, defaultButtonImg, onclickButtonImg, inactiveButtonImg);
	playButton->SetId(0);
	str = "Play";
	playButton->SetText(str);
	playButton->AddEventListener(this);
	m_menuControls.push_back(playButton);

	CButtonUI * exitButton = new CButtonUI();
	exitButton->Init(screenWidth / 2, (screenHeight / 2) + 100,
		defaultButtonImg, onclickButtonImg, inactiveButtonImg);
	exitButton->SetId(1);
	str = "Exit";
	exitButton->SetText(str);
	exitButton->AddEventListener(this);
	m_menuControls.push_back(exitButton);
	
	m_controlManager.AddControl(playButton);
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
		if (sender->GetId() == 0) {
			//init game
			GSetWantedState(ESC_GAME_CONF_MENU);
		} else if (sender->GetId() == 1) {
			GSetWantedState(ESC_EXIT_APP);
		}
		break;
	default:
		break;
	}
}