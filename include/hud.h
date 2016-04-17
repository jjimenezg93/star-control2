#ifndef _C_HUD_H
#define _C_HUD_H

#pragma warning(disable: 4820)

#include "app_state.h"
#include "controlmanagerui.h"
#include "ieventlistener.h"
#include "types.h"
//#include "world.h"
#include "string.h"

#include <vector>

#define NUM_SHIP_STATS 4

class CControlUI;
class CWorld;
class CEntity;
class Font;

class CHud: public IAppState, public IEventListener {
public:
	virtual ~CHud();

	virtual void Init(CEntity * et1, CEntity * et2);

	virtual void Update();
	virtual void Render();

	virtual void ManageControlEvent(CControlUI * const sender);
private:
	void Init();
	struct UIText {
		UIText(uint32 x, uint32 y, String str): m_x(x), m_y(y), m_str(str) {}
		uint32 m_x, m_y;
		String m_str;
	};

	CWorld * m_world;
	CEntity * m_player1;
	CEntity * m_player2;

	CControlManagerUI m_controlManager;
	std::vector<UIText *> m_texts;

	//energy1, hp1, energy2, hp2
	uint16 m_shipStats[NUM_SHIP_STATS];

	Font * m_font;
};

#endif //!_C_HUD_H