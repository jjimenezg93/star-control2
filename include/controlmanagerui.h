#ifndef _C_CONTROL_MANAGER_UI_H
#define _C_CONTROL_MANAGER_UI_H

#include "iregistrable.h"
#include "types.h"

#include <vector>

class CEvent;
class CControlUI;

class CControlManagerUI: public IRegistrable {
public:
	uint8 Init(); // needs CInputManager
	virtual void Notify(const CEvent * const);
	void AddControl(CControlUI * const);
	void RemoveControl(CControlUI * const);

	void Update();
	void Render();
private:
	std::vector<CControlUI *> m_controls;
};

#endif //!_C_CONTROL_MANAGER_UI_H