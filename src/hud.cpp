#include "../include/hud.h"
#include "../include/buttonui.h"
#include "../include/defs.h"
#include "../include/entity.h"
#include "../include/font.h"
#include "../include/image.h"
#include "../include/menu_defs.h"
#include "../include/messages.h"
#include "../include/resourcemanager.h"
#include "../include/renderer.h"
#include "../include/string.h"
#include "../include/screen.h"
#include "../include/world.h"

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

	memset(m_shipStats, 0, sizeof(m_shipStats));
}

void CHud::Init(CWorld * world) {
	Init();
	m_world = world;	
}

void CHud::Update() {
	m_controlManager.Update();

	CEntity * player1;
	CEntity * player2;
	m_world->GetPlayers(player1, player2);

	if (player1 == nullptr) {
		m_shipStats[0] = 0;
		m_shipStats[1] = 0;
	} else {
		SGetEnergyMsg getEnergy1Msg;
		SGetHitPointsMsg getHitPoints1Msg;
		player1->ReceiveMessage(getEnergy1Msg);
		m_shipStats[0] = getEnergy1Msg.GetEnergy();
		player1->ReceiveMessage(getHitPoints1Msg);
		m_shipStats[1] = getHitPoints1Msg.GetHitPoints();
	}

	if (player2 == nullptr) {
		m_shipStats[2] = 0;
		m_shipStats[3] = 0;
	} else {
		SGetEnergyMsg getEnergy2Msg;
		SGetHitPointsMsg getHitPoints2Msg;
		player2->ReceiveMessage(getEnergy2Msg);
		m_shipStats[2] = getEnergy2Msg.GetEnergy();
		player2->ReceiveMessage(getHitPoints2Msg);
		m_shipStats[3] = getHitPoints2Msg.GetHitPoints();
	}
}

void CHud::Render() {
	m_controlManager.Render();
	uint8 i = 0;
	for (std::vector<UIText *>::iterator itr = m_texts.begin();
	itr != m_texts.end(); ++itr) {
		Renderer::Instance().DrawText(m_font,
			(*itr)->m_str + std::to_string(m_shipStats[i++]).c_str(), (*itr)->m_x, (*itr)->m_y);
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
