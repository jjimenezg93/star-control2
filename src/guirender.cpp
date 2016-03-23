#include "../include/guirender.h"
#include "../include/font.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/types.h"

#define FONT_FILENAME "data/monospaced.png"

CGUIRender::CGUIRender() {
	m_fontType = nullptr;
}

CGUIRender::~CGUIRender() {}

uint8 CGUIRender::Init() {
	uint8 ret = 1;
	if (!m_fontType)
		m_fontType = ResourceManager::Instance().LoadFont(FONT_FILENAME);
	if (m_fontType) //not else because it must check it after loading font if first time
		ret = 0;
	m_buttonText = String("");
	return ret;
}

uint8 CGUIRender::Init(Image * const defaultImg, Image * const onClickImg,
	Image * const inactiveImg) {
	uint8 ret = 0;
	ret = Init();
	m_defaultImg = defaultImg;
	m_onClickImg = onClickImg;
	m_inactiveImg = inactiveImg;
	return ret;
}

void CGUIRender::Render(const EGUICurrentState state, const int32 x, const int32 y) {
	Renderer::Instance().DrawImage(GetCurrentImg(state), static_cast<double>(x),
		static_cast<double>(y));
	Renderer::Instance().SetColor(255, 255, 255, 255);
	double textOffset = ((GetCurrImgWidth(state)
		- m_fontType->GetTextWidth(m_buttonText)) / 2);
	Renderer::Instance().DrawText(m_fontType, m_buttonText,
		static_cast<double>(x - GetCurrentImg(state)->GetHandleX()) + textOffset,
		static_cast<double>(y));
}

void CGUIRender::SetDefaultImg(Image * const img) {
	m_defaultImg = img;
}

void CGUIRender::SetOnClickImg(Image * const img) {
	m_onClickImg = img;
}

void CGUIRender::SetInactiveImg(Image * const img) {
	if (img)
		img->SetMidHandle();
	m_inactiveImg = img;
}

Image * const CGUIRender::GetCurrentImg(EGUICurrentState state) const {
	switch (state) {
	case EGUICS_DEFAULT:
		return m_defaultImg;
		break;
	case EGUICS_ONCLICK:
		return m_onClickImg;
		break;
	case EGUICS_INACTIVE:
		return m_inactiveImg;
		break;
	default:
		return nullptr;
		break;
	}
}

uint16 CGUIRender::GetCurrImgWidth(EGUICurrentState state) const {
	return GetCurrentImg(state)->GetWidth() * GetCurrentImg(state)->GetHFrames();
}

uint16 CGUIRender::GetCurrImgHeight(EGUICurrentState state) const {
	return GetCurrentImg(state)->GetHeight() * GetCurrentImg(state)->GetVFrames();
}

void CGUIRender::SetText(const String &newText) {
	m_buttonText = newText;
	float yHandle = static_cast<float>(m_fontType->GetTextHeight(m_buttonText) / 2);
	m_fontType->SetHandle(m_fontType->GetHandleX(), yHandle);
}