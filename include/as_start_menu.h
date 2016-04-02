#ifndef _AS_START_MENU_H
#define _AS_START_MENU_H

#pragma warning(disable: 4820)

#include "app_state.h"
#include "controlmanagerui.h"
#include "ieventlistener.h"
#include "types.h"

#include <vector>

class CControlUI;

class ASStartMenu: public IAppState, public IEventListener {
public:
	virtual ~ASStartMenu();

	virtual void Init();

	virtual void ProcessInput();
	virtual void Update();
	virtual void Render();

	virtual void ManageControlEvent(CControlUI * const sender);
private:
	CControlManagerUI m_controlManager;
};

#endif //!_AS_START_MENU_H