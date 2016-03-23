#include "../include/checkboxui.h"
#include "../include/event.h"
#include "../include/guirender.h"
#include "../include/ieventlistener.h"
#include "../include/image.h"
#include "../include/types.h"
#include "../include/renderer.h"

uint8 CCheckBoxUI::Init() {
	uint8 ret = 0;
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

uint8 CCheckBoxUI::Init(int32 x, int32 y, Image * default, Image * onHover, Image * inactive) {
	uint8 ret = 0;
	ret = Init(x, y);
	GetGUIRender().SetDefaultImg(default);
	GetGUIRender().SetOnClickImg(onHover);
	GetGUIRender().SetInactiveImg(inactive);
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
					if (GetCurrentState() == EGUICS_DEFAULT)
						SetCurrentState(EGUICS_ONCLICK);
					//must be replaced with ControlGroup
					std::vector<CControlUI *>::iterator itr = m_complementaries.begin();
					while (itr != m_complementaries.end()) {
						if ((*itr)->GetType() == ECT_CHECKBOX) {
							((CCheckBoxUI*)(*itr))->UpdateComplementariesState();
						}
						itr++;
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

void CCheckBoxUI::AddComplementary(CControlUI * compl) {
	m_complementaries.push_back(compl);
}

void CCheckBoxUI::UpdateComplementariesState() {
	std::vector<CControlUI *>::iterator itr = m_complementaries.begin();
	while (itr != m_complementaries.end()) {
		if ((*itr)->GetCurrentState() == EGUICS_ONCLICK) {
			SetCurrentState(EGUICS_DEFAULT);
		}

		++itr;
	}
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
