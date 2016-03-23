#include "../include/guirender.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/types.h"

CGUIRender::CGUIRender(Image * const defaultImg, Image * const onClickImg,
		Image * const inactiveImg) {
	m_defaultImg = defaultImg;
	m_onClickImg = onClickImg;
	m_inactiveImg = inactiveImg;
}

CGUIRender::~CGUIRender() {}

void CGUIRender::Render(const EGUICurrentState state, const int32 x, const int32 y) {
	Renderer::Instance().DrawImage(GetCurrentImg(state), static_cast<double>(x),
		static_cast<double>(y));
}

void CGUIRender::SetDefaultImg(Image * const img) {
	if (img)
		img->SetMidHandle();
	m_defaultImg = img;
}

void CGUIRender::SetOnClickImg(Image * const img) {
	if (img)
		img->SetMidHandle();
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