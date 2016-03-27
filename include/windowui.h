#ifndef _C_WINDOW_UI_H
#define _C_WINDOW_UI_H

#include "controlui.h"
#include "guirender.h"

class CWindowUI : public CControlUI {
public:
	virtual ~CWindowUI();

	virtual uint8 Init();
	virtual uint8 Init(int32 x, int32 y);
	virtual uint8 Init(int32 x, int32 y, Image * img);

	virtual void Update();
	virtual void Render();

	//ManageEvent() manages input event and then reproduces it, return says if event was consumed
	virtual bool ManageEvent(const CEvent * const ev);
private:
	int32 m_x, m_y;
};

#endif //!_C_WINDOW_UI_H