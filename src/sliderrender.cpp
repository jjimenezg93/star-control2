#include "../include/buttonui.h"
#include "../include/event.h"
#include "../include/guirender.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/sliderrender.h"

#include <assert.h>

CSliderRender::~CSliderRender() {
	delete m_leftButton;
	delete m_rightButton;
}

uint8 CSliderRender::Init(Image * const bar, Image * const ball, Image * const lDefault,
		Image * const lOnClick, Image * const rDefault, Image * const rOnClick) {
	uint8 ret = 0;
	m_barImg = bar;
	m_ballImg = ball;

	m_leftButton = new CButtonUI();
	assert(m_leftButton != nullptr);
	m_leftButton->Init();
	m_leftButton->SetId(0);

	m_rightButton = new CButtonUI();
	assert(m_rightButton != nullptr);
	m_rightButton->Init();
	m_rightButton->SetId(1);

	SetLButtonImg(lDefault, lOnClick);
	SetRButtonImg(rDefault, rOnClick);

	return ret;
}

void CSliderRender::Render(const ESliderImg img, const int32 x, const int32 y) {
	switch (img) {
	case ESI_BAR:
		Renderer::Instance().DrawImage(m_barImg, static_cast<double>(x), static_cast<double>(y));
		break;
	case ESI_BALL:
		Renderer::Instance().DrawImage(m_ballImg, static_cast<double>(x), static_cast<double>(y));
		break;
	case ESI_LEFT_BUTTON:
		m_leftButton->SetPosition(x, y);
		m_leftButton->Render();
		break;
	case ESI_RIGHT_BUTTON:
		m_rightButton->SetPosition(x, y);
		m_rightButton->Render();
		break;
	default:
		break;
	}
}

void CSliderRender::SetBarImg(Image * const img) {
	m_barImg = img;
}

void CSliderRender::SetBallImg(Image * const img) {
	m_ballImg = img;
}

void CSliderRender::SetLButtonImg(Image * const defaultImg, Image * const onClickImg) {
	m_leftButton->GetGUIRender().SetDefaultImg(defaultImg);
	m_leftButton->GetGUIRender().SetOnClickImg(onClickImg);
}

void CSliderRender::SetRButtonImg(Image * const defaultImg, Image * const onClickImg) {
	m_rightButton->GetGUIRender().SetDefaultImg(defaultImg);
	m_rightButton->GetGUIRender().SetOnClickImg(onClickImg);
}

Image * CSliderRender::GetImage(const ESliderImg eImg) {
	switch (eImg) {
	case ESI_BALL:
		return m_ballImg;
		break;
	case ESI_BAR:
		return m_barImg;
		break;
	case ESI_LEFT_BUTTON:
		return m_leftButton->GetGUIRender().GetCurrentImg(m_leftButton->GetCurrentState());
		break;
	case ESI_RIGHT_BUTTON:
		return m_rightButton->GetGUIRender().GetCurrentImg(m_rightButton->GetCurrentState());
		break;
	default:
		return nullptr;
		break;
	}
}

int32 CSliderRender::GetImageWidth(const ESliderImg eImg) {
	Image * img = GetImage(eImg);
	return img->GetWidth() * img->GetHFrames();
}

int32 CSliderRender::GetImageHeight(const ESliderImg eImg) {
	Image * img = GetImage(eImg);
	return img->GetHeight() * img->GetVFrames();
}

bool CSliderRender::MangeEventButtons(const CEvent * const ev) {
	bool ret = false;

	ret = m_leftButton->ManageEvent(ev);
	ret = m_rightButton->ManageEvent(ev);

	return ret;
}