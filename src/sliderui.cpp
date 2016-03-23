#include "../include/buttonui.h"
#include "../include/event.h"
#include "../include/image.h"
#include "../include/sliderui.h"
#include "../include/sliderrender.h"

#include <assert.h>

#define SLIDER_BUTTON_MARGIN 10

uint8 CSliderUI::Init() {
	SetType(ECT_SLIDER);
	return 0;
}

CSliderUI::~CSliderUI() {}

uint8 CSliderUI::Init(const int32 x, const int32 y, const int32 minVal, const int32 maxVal,
		Image * const bar, Image * const ball, Image * const lDefault,
		Image * const lOnClick, Image * const rDefault, Image * const rOnClick) {
	uint8 ret = 0;
	Init();
	m_x = x;
	m_y = y;

	m_sliderRender.Init(bar, ball, lDefault, lOnClick, rDefault, rOnClick);

	m_sliderRender.GetLButton().AddEventListener(this); //id 0
	m_sliderRender.GetRButton().AddEventListener(this); //id 1

	assert(minVal != maxVal);

	m_minValue = minVal;
	m_maxValue = maxVal;

	m_ballValue = 0;
	
	//ball rate = ImgSize / (max - min)
	m_ballRate = static_cast<float>((bar->GetWidth()) * bar->GetHFrames()
		% (m_maxValue - m_minValue));
	m_ballRate = 1.f; // ballRate is calculated wrong, provisional

	return ret;
}

void CSliderUI::Update() {
	CControlUI::Update();
}

void CSliderUI::Render() {
	int32 offset = 0;

	//lButton
	m_sliderRender.Render(ESI_LEFT_BUTTON, m_x + offset,
		m_y - static_cast<int32>(m_sliderRender.GetImage(ESI_LEFT_BUTTON)->GetHandleY()) / 2);
	offset += m_sliderRender.GetImageWidth(ESI_LEFT_BUTTON)/2 + SLIDER_BUTTON_MARGIN;
	
	//bar
	m_sliderRender.Render(ESI_BAR, m_x + offset,
		m_y - static_cast<int32>(m_sliderRender.GetImage(ESI_BAR)->GetHandleY()));
	
	//ball
	int32 ballPos = static_cast<int32>((m_sliderRender.GetImageWidth(ESI_BAR)
		/ (m_maxValue - m_minValue)) * m_ballValue);

	m_sliderRender.Render(ESI_BALL, m_x + offset + ballPos,	m_y);

	offset += m_sliderRender.GetImageWidth(ESI_BAR)
		+ (m_sliderRender.GetImageWidth(ESI_RIGHT_BUTTON) / 2) + SLIDER_BUTTON_MARGIN;

	//rButton
	m_sliderRender.Render(ESI_RIGHT_BUTTON, m_x + offset,
		m_y - static_cast<int32>(m_sliderRender.GetImage(ESI_RIGHT_BUTTON)->GetHandleY()) / 2);
}

void CSliderUI::ManageControlEvent(CControlUI * const sender) {
	switch (sender->GetType()) {
	case ECT_BUTTON:
		if (sender->GetId() == 0) { //leftButton
			if (m_ballValue - m_ballRate >= 0)
				m_ballValue -= m_ballRate;
			else
				m_ballValue = 0.f;
			NotifyListeners(this);
		} else if (sender->GetId() == 1) { //rightButton
			if (m_ballValue + m_ballRate <= m_maxValue)
				m_ballValue += m_ballRate;
			else
				m_ballValue = static_cast<float>(m_maxValue);
			NotifyListeners(this);
		}
	}
}

float CSliderUI::GetValue() const {
	return m_ballValue;
}

bool CSliderUI::ManageEvent(const CEvent * const ev) {
	bool ret = false;
	ret = m_sliderRender.MangeEventButtons(ev);
	return ret;
}
