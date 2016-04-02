#include "../include/hud.h"
#include "../include/buttonui.h"
#include "../include/defs.h"
#include "../include/image.h"
#include "../include/menu_defs.h"
#include "../include/resourcemanager.h"
#include "../include/string.h"
#include "../include/screen.h"

CHud::~CHud() {
}

void CHud::Init() {
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
	m_controlManager.AddControl(exitButton);
}

void CHud::Update() {
	m_controlManager.Update();
}

void CHud::Render() {
	m_controlManager.Render();
}

void CHud::ManageControlEvent(CControlUI * const sender) {
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
