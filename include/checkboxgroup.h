#ifndef _C_CHECKBOX_GROUP_UI_H
#define _C_CHECKBOX_GROUP_UI_H

#include "controlui.h"
#include "types.h"

#include <vector>

class CCheckBoxUI;

class CCheckBoxGroup: public CControlUI {
public:
	CCheckBoxGroup();
	virtual ~CCheckBoxGroup();

	virtual uint8 Init();

	virtual void Update();
	virtual void Render();

	virtual void AddControl(CControlUI * const control) override;
	virtual bool RemoveControl(CControlUI * const control) override;

	void MarkActiveCheckBox(CControlUI * const control);

	CCheckBoxUI * GetActive() const;
private:
	CCheckBoxUI * m_active;
};

#endif //!_C_CHECKBOX_GROUP_UI_H