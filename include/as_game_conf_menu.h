#ifndef _AS_GAME_CONF_MENU_H
#define _AS_GAME_CONF_MENU_H

#pragma warning(disable: 4820)

#include "app_state.h"
#include "controlmanagerui.h"
#include "ieventlistener.h"
#include "types.h"

#include <vector>

class CControlUI;
class Font;
class String;
struct SEntityParams;

class ASGameConfMenu: public IAppState, public IEventListener {
public:
	virtual ~ASGameConfMenu();

	virtual void Init();

	virtual void ProcessInput();
	virtual void Update();
	virtual void Render();

	virtual void ManageControlEvent(CControlUI * const sender);
private:
	void CreatePlayersParams();
	void ConvertMenuImgToShip(String &str) const;

	CControlManagerUI m_controlManager;

	String * m_text; //manually displaying "IA"
	Font * m_font;
};

#endif //!_AS_GAME_CONF_MENU_H