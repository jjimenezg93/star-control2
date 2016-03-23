#ifndef _C_GUI_RENDER_H
#define _C_GUI_RENDER_H

#include "string.h"
#include "types.h"

class Image;
class Font;

enum EGUICurrentState {
	EGUICS_DEFAULT,
	EGUICS_ONCLICK,
	EGUICS_INACTIVE,
	EGUICS_COUNT //iterating
};

class CGUIRender {
public:
	CGUIRender();
	//images are supposed to have mid handle
	//CGUIRender(Image * const defaultImg, Image * const onClickImg, Image * const inactiveImg);

	~CGUIRender();

	uint8 Init();
	uint8 Init(Image * const defaultImg, Image * const onClickImg, Image * const inactiveImg);

	void Render(const EGUICurrentState state, const int32 x, const int32 y);

	void SetDefaultImg(Image * const img);
	void SetOnClickImg(Image * const img);
	void SetInactiveImg(Image * const img);

	Image * const GetCurrentImg(const EGUICurrentState state) const;
	uint16 GetCurrImgWidth(const EGUICurrentState state) const;
	uint16 GetCurrImgHeight(const EGUICurrentState state) const;

	void SetText(const String &newText);
private:
	Image * m_defaultImg;
	Image * m_onClickImg;
	Image * m_inactiveImg;
	Font * m_fontType;
	String m_buttonText;
};

#endif //!_C_GUI_RENDER_H