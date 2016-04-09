#include "../include/as_game_conf_menu.h"
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

#include <assert.h>

std::vector<SEntityParams> g_entitiesParams;

ASGameConfMenu::~ASGameConfMenu() {
	if (g_wantedState == ESC_EXIT_APP) {
		ResourceManager::Instance().FreeResources();
	}
}

void ASGameConfMenu::Init() {
	String str; //used to send all str's by reference, then copied inside
	m_text = new String("IA (Y/N)");
	m_font = ResourceManager::Instance().LoadFont(FONT_FILENAME);

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

	/* LEFT WINDOW */
	CWindowUI * windowLeft = new CWindowUI();
	windowLeft->Init(screenWidth / 5, screenHeight / 2, windowImg);
	windowLeft->SetId(1);
	m_controlManager.AddControl(windowLeft);

	//player Ship
	CCheckBoxUI * lPlayerShip1 = new CCheckBoxUI();
	lPlayerShip1->Init(screenWidth / 5 - 100, screenHeight / 2 - 100, disabledAvatarImg,
		enabledAvatarImg);
	lPlayerShip1->SetId(0);
	lPlayerShip1->SetCurrentState(EGUICS_ONCLICK);
	m_controlManager.AddControl(lPlayerShip1);
	CCheckBoxUI * lPlayerShip2 = new CCheckBoxUI();
	lPlayerShip2->Init(screenWidth / 5 + 100, screenHeight / 2 - 100, disabledDreadNoughtImg,
		enabledDreadNoughtImg);
	lPlayerShip2->SetId(1);
	m_controlManager.AddControl(lPlayerShip2);

	CCheckBoxGroup * lPlayerShipCBG = new CCheckBoxGroup();
	lPlayerShipCBG->Init();
	lPlayerShipCBG->SetId(0);
	lPlayerShipCBG->AddControl(lPlayerShip1);
	lPlayerShipCBG->AddControl(lPlayerShip2);
	m_controlManager.AddControl(lPlayerShipCBG);

	//playerAI
	CCheckBoxUI * lPlayerAI1 = new CCheckBoxUI();
	lPlayerAI1->Init(screenWidth / 5 - 50, screenHeight / 2 + 50, disabledCheckBoxImg,
		enabledCheckBoxImg);
	lPlayerAI1->SetId(2);
	lPlayerAI1->SetCurrentState(EGUICS_ONCLICK);
	m_controlManager.AddControl(lPlayerAI1);
	CCheckBoxUI * lPlayerAI2 = new CCheckBoxUI();
	lPlayerAI2->Init(screenWidth / 5 + 50, screenHeight / 2 + 50, disabledCheckBoxImg,
		enabledCheckBoxImg);
	lPlayerAI2->SetId(3);
	m_controlManager.AddControl(lPlayerAI2);

	CCheckBoxGroup * lPlayerAICBG = new CCheckBoxGroup();
	lPlayerAICBG->Init();
	lPlayerAICBG->SetId(1);
	lPlayerAICBG->AddControl(lPlayerAI1);
	lPlayerAICBG->AddControl(lPlayerAI2);
	m_controlManager.AddControl(lPlayerAICBG);

	/* CENTER WINDOW */
	CWindowUI * windowCenter = new CWindowUI();
	windowCenter->Init(screenWidth / 2, screenHeight / 2, windowImg);
	windowCenter->SetId(2);
	m_controlManager.AddControl(windowCenter);

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
	str = "Back";
	exitButton->SetText(str);
	exitButton->AddEventListener(this);
	m_controlManager.AddControl(exitButton);

	/* RIGHT WINDOW */
	CWindowUI * windowRight = new CWindowUI();
	windowRight->Init(screenWidth / 5 * 4, screenHeight / 2, windowImg);
	windowRight->SetId(3);
	m_controlManager.AddControl(windowRight);

	//player Ship
	CCheckBoxUI * rPlayerShip1 = new CCheckBoxUI();
	rPlayerShip1->Init(screenWidth / 5 * 4 - 100, screenHeight / 2 - 100, disabledAvatarImg,
		enabledAvatarImg);
	rPlayerShip1->SetId(4);
	rPlayerShip1->SetCurrentState(EGUICS_ONCLICK);
	m_controlManager.AddControl(rPlayerShip1);
	CCheckBoxUI * rPlayerShip2 = new CCheckBoxUI();
	rPlayerShip2->Init(screenWidth / 5 * 4 + 100, screenHeight / 2 - 100, disabledDreadNoughtImg,
		enabledDreadNoughtImg);
	rPlayerShip2->SetId(5);
	m_controlManager.AddControl(rPlayerShip2);

	CCheckBoxGroup * rPlayerShipCBG = new CCheckBoxGroup();
	rPlayerShipCBG->Init();
	rPlayerShipCBG->SetId(2);
	rPlayerShipCBG->AddControl(rPlayerShip1);
	rPlayerShipCBG->AddControl(rPlayerShip2);
	m_controlManager.AddControl(rPlayerShipCBG);

	//playerAI
	CCheckBoxUI * rPlayerAI1 = new CCheckBoxUI();
	rPlayerAI1->Init(screenWidth / 5 * 4 - 50, screenHeight / 2 + 50, disabledCheckBoxImg,
		enabledCheckBoxImg);
	rPlayerAI1->SetId(6);
	rPlayerAI1->SetCurrentState(EGUICS_ONCLICK);
	m_controlManager.AddControl(rPlayerAI1);
	CCheckBoxUI * rPlayerAI2 = new CCheckBoxUI();
	rPlayerAI2->Init(screenWidth / 5 * 4 + 50, screenHeight / 2 + 50, disabledCheckBoxImg,
		enabledCheckBoxImg);
	rPlayerAI2->SetId(7);
	m_controlManager.AddControl(rPlayerAI2);

	CCheckBoxGroup * rPlayerAICBG = new CCheckBoxGroup();
	rPlayerAICBG->Init();
	rPlayerAICBG->SetId(3);
	rPlayerAICBG->AddControl(rPlayerAI1);
	rPlayerAICBG->AddControl(rPlayerAI2);
	m_controlManager.AddControl(rPlayerAICBG);
}

void ASGameConfMenu::ProcessInput() {
	CInputManager::Instance().Update();
}

void ASGameConfMenu::Update() {
	m_controlManager.Update();
}

void ASGameConfMenu::Render() {
	Renderer::Instance().Clear();
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	m_controlManager.Render();

	Renderer::Instance().DrawText(m_font, *m_text,
		Screen::Instance().GetWidth() / 5 - m_font->GetTextWidth(*m_text) / 2,
		Screen::Instance().GetHeight() / 2);
	Renderer::Instance().DrawText(m_font, *m_text,
		Screen::Instance().GetWidth() / 5 * 4 - m_font->GetTextWidth(*m_text) / 2,
		Screen::Instance().GetHeight() / 2);

	Screen::Instance().Refresh();
}

void ASGameConfMenu::ManageControlEvent(CControlUI * const sender) {
	switch (sender->GetType()) {
	case ECT_BUTTON:
		if (sender->GetId() == 0) {
			GSetWantedState(ESC_GAME);
			CreatePlayersParams();
		} else if (sender->GetId() == 1) {
			GSetWantedState(ESC_START_MENU);
		}
		break;
	default:
		break;
	}
}

void ASGameConfMenu::CreatePlayersParams() {
	CControlUI * control = nullptr;
	String shipName;
	bool isAI = true;

	/* PLAYER 1 */
	//name
	if (m_controlManager.GetControlState(ECT_CHECKBOX, 0) == EGUICS_ONCLICK) {
		control = m_controlManager.GetControl(ECT_CHECKBOX, 0);
	} else if (m_controlManager.GetControlState(ECT_CHECKBOX, 1) == EGUICS_ONCLICK) {
		control = m_controlManager.GetControl(ECT_CHECKBOX, 1);
	}
	assert(control != nullptr && "Player1 ship checkbox control is nullptr");
	shipName = ((CCheckBoxUI *)(control))->GetGUIRender().GetCurrentImg(EGUICS_ONCLICK)->
		GetFilename().StripDir().StripExt();
	ConvertMenuImgToShip(shipName);

	//isAI
	if (m_controlManager.GetControlState(ECT_CHECKBOX, 2) == EGUICS_ONCLICK) {
		isAI = true;
	} else if (m_controlManager.GetControlState(ECT_CHECKBOX, 3) == EGUICS_ONCLICK) {
		isAI = false;
	}
	g_entitiesParams.push_back(SEntityParams(shipName, isAI, EGameSide::EGS_PLAYER_1));

	/* PLAYER 2 */
	//name
	if (m_controlManager.GetControlState(ECT_CHECKBOX, 4) == EGUICS_ONCLICK) {
		control = m_controlManager.GetControl(ECT_CHECKBOX, 4);
	} else if (m_controlManager.GetControlState(ECT_CHECKBOX, 5) == EGUICS_ONCLICK) {
		control = m_controlManager.GetControl(ECT_CHECKBOX, 5);
	}
	assert(control != nullptr && "Player2 ship checkbox control is nullptr");
	shipName = ((CCheckBoxUI *)(control))->GetGUIRender().GetCurrentImg(EGUICS_ONCLICK)->
		GetFilename().StripDir().StripExt();
	ConvertMenuImgToShip(shipName);

	//isAI
	if (m_controlManager.GetControlState(ECT_CHECKBOX, 6) == EGUICS_ONCLICK) {
		isAI = true;
	} else if (m_controlManager.GetControlState(ECT_CHECKBOX, 7) == EGUICS_ONCLICK) {
		isAI = false;
	}
	g_entitiesParams.push_back(SEntityParams(shipName, isAI, EGameSide::EGS_PLAYER_2));
}

void ASGameConfMenu::ConvertMenuImgToShip(String &str) const{
	if (str == "avatar_enabled") {
		str = "avatar";
	} else if (str == "dreadnought_enabled") {
		str = "dreadnought";
	}
}