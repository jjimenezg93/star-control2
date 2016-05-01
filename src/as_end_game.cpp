#include <assert.h>
#include <string>
#include <vector>

#include "../include/as_end_game.h"
#include "../include/buttonui.h"
#include "../include/checkboxgroup.h"
#include "../include/checkboxui.h"
#include "../include/controlui.h"
#include "../include/defs.h"
#include "../include/entity_params.h"
#include "../include/font.h"
#include "../include/inputmanager.h"
#include "../include/image.h"
#include "../include/menu_defs.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/screen.h"
#include "../include/string.h"
#include "../include/windowui.h"

ASEndGameMenu::~ASEndGameMenu() {
	if (g_wantedState == ESC_EXIT_APP) {
		ResourceManager::Instance().FreeResources();
	}
}

void ASEndGameMenu::Init() {
	String str; //used to send all str's by reference, then copied inside

	m_text = new String(" WINNER: ");
	m_font = ResourceManager::Instance().LoadFont(FONT_FILENAME);
	
	m_winnerImg = GetShipImage(
		(static_cast<SShipParams *>(g_entitiesParams.at(g_winner)))->GetShipName());

	Image * defaultButtonImg = ResourceManager::Instance().LoadImage(BUTTON_DEFAULT_IMG);
	defaultButtonImg->SetMidHandle();
	Image * onclickButtonImg = ResourceManager::Instance().LoadImage(BUTTON_ONCLICK_IMG);
	onclickButtonImg->SetMidHandle();
	Image * inactiveButtonImg = ResourceManager::Instance().LoadImage(BUTTON_INACTIVE_IMG);
	inactiveButtonImg->SetMidHandle();

	Image * windowImg = ResourceManager::Instance().LoadImage(WINDOW_LONG_HEIGHT_IMG);
	windowImg->SetMidHandle();

	Image * enabledCheckBoxImg = ResourceManager::Instance().LoadImage(CHECKBOX_ENABLED_IMG);
	enabledCheckBoxImg->SetMidHandle();

	Image * disabledCheckBoxImg = ResourceManager::Instance().LoadImage(CHECKBOX_DISABLED_IMG);
	disabledCheckBoxImg->SetMidHandle();

	Image * enabledAvatarImg = ResourceManager::Instance().LoadImage(AVATAR_ENABLED_IMG);
	enabledAvatarImg->SetMidHandle();
	Image * disabledAvatarImg = ResourceManager::Instance().LoadImage(AVATAR_DISABLED_IMG);
	disabledAvatarImg->SetMidHandle();

	Image * enabledDreadNoughtImg = ResourceManager::Instance().LoadImage(
		DREADNOUGHT_ENABLED_IMG);
	enabledDreadNoughtImg->SetMidHandle();
	Image * disabledDreadNoughtImg = ResourceManager::Instance().LoadImage(
		DREADNOUGHT_DISABLED_IMG);
	disabledDreadNoughtImg->SetMidHandle();

	Image * backgroundImg = ResourceManager::Instance().LoadImage(MENU_BACKGROUND_IMG);

	uint16 screenWidth = Screen::Instance().GetWidth();
	uint16 screenHeight = Screen::Instance().GetHeight();

	m_controlManager.Init();

	//Background
	CWindowUI * background = new CWindowUI();
	background->Init(0, 0, backgroundImg);
	background->SetId(0);
	m_controlManager.AddControl(background);

	/* CENTER WINDOW */
	CWindowUI * windowCenter = new CWindowUI();
	windowCenter->Init(screenWidth / 2, screenHeight / 2, windowImg);
	windowCenter->SetId(2);
	m_controlManager.AddControl(windowCenter);

	CButtonUI * playButton = new CButtonUI();
	playButton->Init(screenWidth / 2, screenHeight / 2 - 100,
		defaultButtonImg, onclickButtonImg, inactiveButtonImg);
	playButton->SetId(0);
	str = "Play again";
	playButton->SetText(str);
	playButton->AddEventListener(this);
	m_controlManager.AddControl(playButton);

	CButtonUI * exitButton = new CButtonUI();
	exitButton->Init(screenWidth / 2, (screenHeight / 2) + 100,
		defaultButtonImg, onclickButtonImg, inactiveButtonImg);
	exitButton->SetId(1);
	str = "Exit";
	exitButton->SetText(str);
	exitButton->AddEventListener(this);
	m_controlManager.AddControl(exitButton);
}

void ASEndGameMenu::ProcessInput() {
	CInputManager::Instance().Update();
}

void ASEndGameMenu::Update() {
	m_controlManager.Update();
}

void ASEndGameMenu::Render() {
	Renderer::Instance().Clear();
	IAppState::Render();
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	m_controlManager.Render();

	Renderer::Instance().DrawText(m_font, *m_text,
		Screen::Instance().GetWidth() / 2 - m_font->GetTextWidth(*m_text) / 2,
		Screen::Instance().GetHeight() / 2 - m_font->GetTextHeight(*m_text) / 2 - 50);

	Renderer::Instance().DrawImage(m_winnerImg,
		Screen::Instance().GetWidth() / 2,
		Screen::Instance().GetHeight() / 2);

	Screen::Instance().Refresh();
}

void ASEndGameMenu::ManageControlEvent(CControlUI * const sender) {
	switch (sender->GetType()) {
	case ECT_BUTTON:
		if (sender->GetId() == 0) {
			GSetWantedState(ESC_GAME_CONF_MENU);
		} else if (sender->GetId() == 1) {
			GSetWantedState(ESC_EXIT_APP);
		}
		break;
	default:
		break;
	}
}

Image * ASEndGameMenu::GetShipImage(std::string shipName) {
	std::string str("data/");
	str += shipName + "/" + shipName + "_ship.png"; //image path has to be constructed
	return ResourceManager::Instance().LoadImage(str.c_str(), 1, 1);
}
