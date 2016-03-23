#include "../include/checkboxgroup.h"
#include "../include/checkboxui.h"

CCheckBoxGroup::CCheckBoxGroup() {}

CCheckBoxGroup::~CCheckBoxGroup() {}

uint8 CCheckBoxGroup::Init() {
	uint8 ret = 0;
	SetType(ECT_CHECKBOX_GROUP);
	return ret;
}

void CCheckBoxGroup::Update() {
	CControlUI::Update();
}

void CCheckBoxGroup::Render() {
	CControlUI::Render();
}

void CCheckBoxGroup::AddControl(CControlUI * const control) {
	if (control->GetType() == ECT_CHECKBOX) {
		CControlUI::AddControl(control);
		reinterpret_cast<CCheckBoxUI *>(control)->m_group = this;
	}
}

bool CCheckBoxGroup::RemoveControl(CControlUI * const control) {
	bool ret = false;
	if (control->GetType() == ECT_CHECKBOX) {
		if (CControlUI::RemoveControl(control)) {
			reinterpret_cast<CCheckBoxUI *>(control)->m_group = nullptr;
			ret = true;
		}
	}
	return ret;
}

void CCheckBoxGroup::MarkActiveCheckBox(CControlUI * const control) {
	const std::vector<CControlUI *> controls = GetControls();
	for (std::vector<CControlUI *>::const_iterator itr = controls.begin();
	itr != controls.end(); ++itr) {
		if ((*itr)->GetType() == ECT_CHECKBOX) {
			if ((*itr) == control)
				(*itr)->SetCurrentState(EGUICS_ONCLICK);
			else
				(*itr)->SetCurrentState(EGUICS_DEFAULT);
		}
	}
}
