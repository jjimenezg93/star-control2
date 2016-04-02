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
#include "../include/windowui.h"

#include <iostream>

ASStartMenu::~ASStartMenu() {
	if (g_wantedState == ESC_EXIT_APP) {
		ResourceManager::Instance().FreeResources();
	}
}

void ASStartMenu::Init() {
	String str; //used to send all str's by reference, then copied inside

	Image * defaultButtonImg = ResourceManager::Instance().LoadImage(BUTTON_DEFAULT_IMG);
	defaultButtonImg->SetMidHandle();
	Image * onclickButtonImg = ResourceManager::Instance().LoadImage(BUTTON_ONCLICK_IMG);
	onclickButtonImg->SetMidHandle();
	Image * inactiveButtonImg = ResourceManager::Instance().LoadImage(BUTTON_INACTIVE_IMG);
	inactiveButtonImg->SetMidHandle();

	Image * windowImg = ResourceManager::Instance().LoadImage(WINDOW_DEFAULT_IMG);
	windowImg->SetMidHandle();

	Image * backgroundImg = ResourceManager::Instance().LoadImage(MENU_BACKGROUND_IMG);

	uint16 screenWidth = Screen::Instance().GetWidth();
	uint16 screenHeight = Screen::Instance().GetHeight();

	m_controlManager.Init();

	//Background
	CWindowUI * background = new CWindowUI();
	background->Init(0, 0, backgroundImg);
	background->SetId(0);
	m_controlManager.AddControl(background);

	//Window
	CWindowUI * window = new CWindowUI();
	window->Init(screenWidth / 2, screenHeight / 2, windowImg);
	window->SetId(1);
	m_controlManager.AddControl(window);

	//Buttons
	CButtonUI * playButton = new CButtonUI();
	playButton->Init(screenWidth / 2, screenHeight / 2 - 50,
		defaultButtonImg, onclickButtonImg, inactiveButtonImg);
	playButton->SetId(0);
	str = "Play";
	playButton->SetText(str);
	playButton->AddEventListener(this);
	m_controlManager.AddControl(playButton);

	CButtonUI * exitButton = new CButtonUI();
	exitButton->Init(screenWidth / 2, (screenHeight / 2) + 50,
		defaultButtonImg, onclickButtonImg, inactiveButtonImg);
	exitButton->SetId(1);
	str = "Exit";
	exitButton->SetText(str);
	exitButton->AddEventListener(this);
	m_controlManager.AddControl(exitButton);
}

void ASStartMenu::ProcessInput() {
	CInputManager::Instance().Update();
}

void ASStartMenu::Update() {	
	m_controlManager.Update();
}

void ASStartMenu::Render() {
	Renderer::Instance().Clear();
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	m_controlManager.Render();

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