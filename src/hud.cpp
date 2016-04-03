#include "../include/hud.h"
#include "../include/buttonui.h"
#include "../include/defs.h"
#include "../include/font.h"
#include "../include/image.h"
#include "../include/menu_defs.h"
#include "../include/resourcemanager.h"
#include "../include/renderer.h"
#include "../include/string.h"
#include "../include/screen.h"

CHud::~CHud() {
}

void CHud::Init() {
	String str = "";

	m_font = ResourceManager::Instance().LoadFont(FONT_FILENAME);

	Image * defaultButtonImg = ResourceManager::Instance().LoadImage(BUTTON_DEFAULT_IMG);
	defaultButtonImg->SetMidHandle();
	Image * onClickButtonImg = ResourceManager::Instance().LoadImage(BUTTON_ONCLICK_IMG);
	onClickButtonImg->SetMidHandle();

	int32 x = Screen::Instance().GetWidth() + static_cast<int32>(defaultButtonImg->GetHandleX())
		- (defaultButtonImg->GetWidth() * defaultButtonImg->GetHFrames());
	int32 y = Screen::Instance().GetHeight() + static_cast<int32>(defaultButtonImg->GetHandleY())
		- defaultButtonImg->GetHeight() * defaultButtonImg->GetVFrames();

	m_controlManager.Init();
	str = "P1_energy:";
	m_texts.push_back(new UIText(0, m_font->GetTextHeight(str), str));
	str = "P1_HP:";
	m_texts.push_back(new UIText(0, m_font->GetTextHeight(str) * 2, str));
	str = "P2_energy:";
	m_texts.push_back(new UIText(0,
		Screen::Instance().GetHeight() - m_font->GetTextHeight(str) * 2, str));
	str = "P2_HP:";
	m_texts.push_back(new UIText(0,
		Screen::Instance().GetHeight() - m_font->GetTextHeight(str), str));

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
	for (std::vector<UIText *>::iterator itr = m_texts.begin();
	itr != m_texts.end(); ++itr) {
		Renderer::Instance().DrawText(m_font, (*itr)->m_str, (*itr)->m_x, (*itr)->m_y);
	}
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
