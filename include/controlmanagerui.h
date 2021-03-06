#ifndef _C_CONTROL_MANAGER_UI_H
#define _C_CONTROL_MANAGER_UI_H

#include "iregistrable.h"
#include "types.h"

#include <vector>

class CEvent;
class CControlUI;
enum EGUICurrentState;
enum EControlType;

class CControlManagerUI: public IRegistrable {
public:
	CControlManagerUI::~CControlManagerUI();

	uint8 Init(); // needs CInputManager
	virtual void Notify(const CEvent * const);
	void AddControl(CControlUI * const);
	bool RemoveControl(CControlUI * const);

	void Update();
	void Render();

	EGUICurrentState GetControlState(EControlType type, int32 id) const;
	CControlUI * GetControl(EControlType type, int32 id);
private:
	std::vector<CControlUI *> m_controls;
};

#endif //!_C_CONTROL_MANAGER_UI_H