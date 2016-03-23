#ifndef _C_CONTROL_UI_H
#define _C_CONTROL_UI_H

#include "guirender.h"
#include "types.h"

#include <vector>

enum EControlType {
	ECT_BASE_CONTROL,
	ECT_BUTTON,
	ECT_SLIDER,
	ECT_CHECKBOX,
	ECT_CHECKBOX_GROUP,
	ECT_COUNT
};

class CEvent;
class SMessage;
class IEventListener;
class CGUIRender;
enum EGUICurrentState;

class CControlUI {
public:
	virtual ~CControlUI();

	virtual uint8 Init() = 0;

	virtual void Update();
	virtual void Render();

	//ManageEvent() manages input event and then reproduces it, return says if event was consumed
	virtual bool ManageEvent(const CEvent * const ev);

	virtual void AddEventListener(IEventListener * const eventListener);
	virtual void RemoveEventListener(IEventListener * const eventListener);

	virtual void AddControl(CControlUI * const control);
	virtual bool RemoveControl(CControlUI * const control);

	int32 GetId() const { return m_id; }
	void SetId(int32 id) { m_id = id; }

	EControlType GetType() const { return m_type; }

	CGUIRender & GetGUIRender();
	void SetCurrentState(const EGUICurrentState newState);
	EGUICurrentState GetCurrentState() const { return m_currentState; }
protected:
	void SetType(const EControlType type);
	void NotifyListeners(CControlUI * const sender);
	const std::vector<CControlUI *> & GetControls() const; //read-only
private:
	std::vector<IEventListener *> m_listeners;
	std::vector<CControlUI *> m_controls;

	int32 m_id;
	EControlType m_type;
	CGUIRender m_guirender;
	EGUICurrentState m_currentState;
};

#endif //!_C_CONTROL_UI_H