#ifndef _C_SLIDER_UI_H
#define _C_SLIDER_UI_H

#include "controlui.h"
#include "ieventlistener.h"
#include "sliderrender.h"
#include "types.h"

class CSliderUI: public CControlUI, public IEventListener {
public:
	CSliderUI() {}
	~CSliderUI();

	uint8 Init();
	uint8 Init(const int32 x, const int32 y, const int32 minVal, const int32 maxVal,
		Image * const bar, Image * const ball, Image * const lDefault,
		Image * const lOnClick, Image * const rDefault, Image * const rOnClick);

	virtual void Update();
	virtual void Render();

	virtual void ManageControlEvent(CControlUI * const sender);

	float GetValue() const;

	virtual bool ManageEvent(const CEvent * const ev);
private:
	int32 m_x, m_y;
	float m_ballValue, m_ballRate;
	uint32 m_minValue, m_maxValue;
	CSliderRender m_sliderRender;
};

#endif //!_C_SLIDER_UI_H