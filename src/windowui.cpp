#include "../include/windowui.h"

CWindowUI::~CWindowUI() {}

uint8 CWindowUI::Init() {
	uint8 ret = 0;
	ret = GetGUIRender().Init();
	SetType(ECT_WINDOW);
	SetCurrentState(EGUICS_DEFAULT);
	return ret;
}

uint8 CWindowUI::Init(int32 x, int32 y) {
	uint8 ret = 0;
	ret = Init();
	m_x = x;
	m_y = y;
	return ret;
}

uint8 CWindowUI::Init(int32 x, int32 y, Image * defaultImg) {
	uint8 ret = 0;
	ret = Init(x, y);
	GetGUIRender().SetDefaultImg(defaultImg);
	return ret;
}

void CWindowUI::Update() {
	CControlUI::Update();
}

void CWindowUI::Render() {
	GetGUIRender().Render(GetCurrentState(), m_x, m_y);
	CControlUI::Render();
}

bool CWindowUI::ManageEvent(const CEvent * const ev) {
	bool consumed = false;
	consumed = CControlUI::ManageEvent(ev);
	return consumed;
}