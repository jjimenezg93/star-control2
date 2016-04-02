#ifndef _C_HUD_H
#define _C_HUD_H

#pragma warning(disable: 4820)

#include "app_state.h"
#include "controlmanagerui.h"
#include "ieventlistener.h"
#include "types.h"
#include "world.h"

#include <vector>

class CControlUI;
class Font;
class String;

class CHud: public IAppState, public IEventListener {
public:
	virtual ~CHud();

	virtual void Init();

	virtual void Update();
	virtual void Render();

	virtual void ManageControlEvent(CControlUI * const sender);
private:
	struct UIText {
		UIText(uint32 x, uint32 y, String * str): m_x(x), m_y(y), m_str(str) {}
		uint32 m_x, m_y;
		String * m_str;
	};

	CControlManagerUI m_controlManager;

	String * m_text;
	Font * m_font;
};

#endif //!_C_HUD_H