#ifndef _C_CHECKBOX_UI_H
#define _C_CHECKBOX_UI_H

#include "controlui.h"
#include "types.h"

#include <vector>

class IEventListener;
class CGUIRender;

class CCheckBoxUI: public CControlUI {
public:
	CCheckBoxUI() {}

	~CCheckBoxUI();

	virtual uint8 Init();
	uint8 Init(int32 x, int32 y);
	uint8 Init(int32 x, int32 y, Image * default, Image * onHover, Image * inactive = nullptr);

	virtual void Update();
	virtual void Render();

	virtual bool ManageEvent(const CEvent * const ev);
private:
	friend class CCheckBoxGroup;
	bool MouseIsOver(const CEvent * const ev);
	
	int32 m_x, m_y;

	std::vector<CControlUI *> m_complementaries;
	CCheckBoxGroup * m_group;
};

#endif //!_C_CHECKBOX_UI_H