#include "../include/checkboxui.h"
#include "../include/checkboxgroup.h"
#include "../include/event.h"
#include "../include/guirender.h"
#include "../include/ieventlistener.h"
#include "../include/image.h"
#include "../include/types.h"
#include "../include/renderer.h"

CCheckBoxUI::~CCheckBoxUI() {}

uint8 CCheckBoxUI::Init() {
	uint8 ret = 0;
	ret = GetGUIRender().Init();
	return ret;
}

uint8 CCheckBoxUI::Init(int32 x, int32 y) {
	uint8 ret = 0;
	ret = Init();
	m_x = x;
	m_y = y;
	SetType(ECT_CHECKBOX);
	SetCurrentState(EGUICS_DEFAULT);
	return ret;
}

uint8 CCheckBoxUI::Init(int32 x, int32 y, Image * defaultImg,
		Image * onClickImg, Image * inactiveImg) {
	uint8 ret = 0;
	ret = Init(x, y);
	ret = GetGUIRender().Init(defaultImg, onClickImg, inactiveImg);
	return ret;
}

void CCheckBoxUI::Update() {
	CControlUI::Update();
}

void CCheckBoxUI::Render() {
	GetGUIRender().Render(GetCurrentState(), m_x, m_y);
	CControlUI::Render();
}

bool CCheckBoxUI::ManageEvent(const CEvent * const ev) {
	bool consumed = false;
	if (GetCurrentState() != EGUICS_INACTIVE) {
		if (ev->GetController() == EEC_MOUSE) {
			switch (ev->GetId()) {
			case EME_LMB_CLICK:
				if (MouseIsOver(ev)) {
					if (GetCurrentState() == EGUICS_DEFAULT) {
						SetCurrentState(EGUICS_ONCLICK);
						m_group->MarkActiveCheckBox(this);
					}
					consumed = true;
				}
				break;
			default:
				break;
			}

		}
	}
	return consumed;
}

bool CCheckBoxUI::MouseIsOver(const CEvent * const ev) {
	uint16 width = GetGUIRender().GetCurrImgWidth(GetCurrentState());
	uint16 height = GetGUIRender().GetCurrImgHeight(GetCurrentState());

	if (ev->GetX() >= m_x - (width / 2) && ev->GetX() <= m_x + (width / 2)
		&& ev->GetY() >= m_y - (height / 2) && ev->GetY() <= m_y + (height / 2)) {
		return true;
	} else {
		return false;
	}
}
