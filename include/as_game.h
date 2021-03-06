#ifndef _AS_GAME_H
#define _AS_GAME_H

#pragma warning(disable: 4820)

#include "app_state.h"
#include "controlmanagerui.h"
#include "ieventlistener.h"
#include "hud.h"
#include "types.h"
#include "world.h"

#include <vector>

class CControlUI;
class CEntity;
class Font;
class String;

class ASGame: public IAppState, public IEventListener {
public:
	virtual ~ASGame();

	virtual void Init();

	virtual void ProcessInput();
	virtual void Update();
	virtual void Render();

	virtual void ManageControlEvent(CControlUI * const sender);
private:
	struct UIText {
		UIText(uint32 x, uint32 y, String * str): m_x(x), m_y(y), m_str(str) {}
		uint32 m_x, m_y;
		String * m_str;
	};

	//CControlManagerUI m_controlManager;
	CHud m_hud;

	CWorld m_world;
};

#endif //!_AS_GAME_H