#include "../include/as_game.h"
#include "../include/buttonui.h"
#include "../include/controlui.h"
#include "../include/defs.h"
#include "../include/font.h"
#include "../include/image.h"
#include "../include/inputmanager.h"
#include "../include/menu_defs.h"
#include "../include/resourcemanager.h"
#include "../include/renderer.h"
#include "../include/screen.h"

ASGame::~ASGame() {
	if (g_wantedState == ESC_EXIT_APP) {
		ResourceManager::Instance().FreeResources();
	}
	for (std::vector<CControlUI *>::iterator itr = m_menuControls.begin();
	itr != m_menuControls.end(); ++itr) {
		m_controlManager.RemoveControl((*itr));
		delete (*itr);
	}
	m_menuControls.clear();
}


void ASGame::Init() {
	String str = "";
	Image * defaultButtonImg = ResourceManager::Instance().LoadImage(BUTTON_DEFAULT_IMG);
	defaultButtonImg->SetMidHandle();
	Image * onClickButtonImg = ResourceManager::Instance().LoadImage(BUTTON_ONCLICK_IMG);
	onClickButtonImg->SetMidHandle();

	int32 x = Screen::Instance().GetWidth() + static_cast<int32>(defaultButtonImg->GetHandleX())
		- (defaultButtonImg->GetWidth() * defaultButtonImg->GetHFrames());
	int32 y = Screen::Instance().GetHeight() + static_cast<int32>(defaultButtonImg->GetHandleY())
		- defaultButtonImg->GetHeight() * defaultButtonImg->GetVFrames();

	m_controlManager.Init();

	CButtonUI * exitButton = new CButtonUI();
	exitButton->Init(x, y, defaultButtonImg, onClickButtonImg);
	exitButton->SetId(0);
	str = "Exit";
	exitButton->SetText(str);
	exitButton->AddEventListener(this);
	m_menuControls.push_back(exitButton);

	//adding to controlManager all private menuControls
	for (std::vector<CControlUI *>::iterator itr = m_menuControls.begin();
	itr != m_menuControls.end(); itr++) {
		m_controlManager.AddControl((*itr));
	}
}

void ASGame::ProcessInput() {
	CInputManager::Instance().Update();
}

void ASGame::Update() {
	m_controlManager.Update();
}

void ASGame::Draw() {
	Renderer::Instance().Clear();
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	m_controlManager.Render();

	Screen::Instance().Refresh();
}

void ASGame::ManageControlEvent(CControlUI * const sender) {
	switch (sender->GetType()) {
	case ECT_BUTTON:
		if (sender->GetId() == 0) {
			GSetWantedState(ESC_GAME_CONF_MENU);
		}
		break;
	default:
		break;
	}
}
