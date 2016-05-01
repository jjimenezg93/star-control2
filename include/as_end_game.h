#ifndef _AS_END_GAME_MENU_H
#define _AS_END_GAME_MENU_H

#pragma warning(disable: 4820)

#include <vector>
#include <string>

#include "app_state.h"
#include "controlmanagerui.h"
#include "ieventlistener.h"
#include "types.h"

class CControlUI;
class Font;
class Image;
class String;
struct SEntityParams;

class ASEndGameMenu: public IAppState, public IEventListener {
public:
	virtual ~ASEndGameMenu();

	virtual void Init();

	virtual void ProcessInput();
	virtual void Update();
	virtual void Render();

	virtual void ManageControlEvent(CControlUI * const sender);
private:
	Image * GetShipImage(std::string shipName);

	CControlManagerUI m_controlManager;

	Image * m_winnerImg;

	Font * m_font;
	String * m_text;
};

#endif //!_AS_END_GAME_MENU_H