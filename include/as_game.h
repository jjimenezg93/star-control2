#ifndef _AS_GAME_H
#define _AS_GAME_H

#pragma warning(disable: 4820)

#include "app_state.h"
#include "controlmanagerui.h"
#include "ieventlistener.h"
#include "types.h"

#include <vector>

class CControlUI;
class Font;
class String;

class ASGame: public IAppState, public IEventListener {
public:
	virtual ~ASGame();

	virtual void Init();

	virtual void ProcessInput();
	virtual void Update();
	virtual void Draw();

	virtual void ManageControlEvent(CControlUI * const sender);
private:
	struct UIText {
		UIText(uint32 x, uint32 y, String * str): m_x(x), m_y(y), m_str(str) {}
		uint32 m_x, m_y;
		String * m_str;
	};
	std::vector<CControlUI *> m_menuControls;

	CControlManagerUI m_controlManager;

	String * m_text;
	Font * m_font;
};

#endif //!_AS_GAME_H