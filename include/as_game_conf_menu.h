#ifndef _AS_GAME_CONF_MENU_H
#define _AS_GAME_CONF_MENU_H

#pragma warning(disable: 4820)

#include "app_state.h"
#include "controlmanagerui.h"
#include "ieventlistener.h"
#include "types.h"

#include <vector>

class CControlUI;

class ASGameConfMenu: public IAppState, public IEventListener {
public:
	virtual ~ASGameConfMenu();

	virtual void Init();

	virtual void ProcessInput();
	virtual void Update();
	virtual void Draw();

	virtual void ManageControlEvent(CControlUI * const sender);
private:
	std::vector<CControlUI *> m_menuControls;

	CControlManagerUI m_controlManager;
};

#endif //!_AS_GAME_CONF_MENU_H