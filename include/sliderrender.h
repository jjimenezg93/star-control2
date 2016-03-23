#ifndef _C_SLIDER_RENDER_H
#define _C_SLIDER_RENDER_H

#include "types.h"

class Image;
class CButtonUI;

enum ESliderImg {
	ESI_BAR,
	ESI_BALL,
	ESI_LEFT_BUTTON,
	ESI_RIGHT_BUTTON
};

class CSliderRender {
public:
	CSliderRender() {}
	~CSliderRender();

	uint8 Init(Image * const bar, Image * const ball, Image * const lDefault,
		Image * const lOnClick, Image * const rDefault, Image * const rOnClick);

	void Render(const ESliderImg eImg, const int32 x, const int32 y);

	void SetBarImg(Image * const img);
	void SetBallImg(Image * const img);
	void SetLButtonImg(Image * const defaultImg, Image * const onClickImg);
	void SetRButtonImg(Image * const defaultImg, Image * const onClickImg);

	Image * GetImage(const ESliderImg eImg);

	int32 GetImageWidth(const ESliderImg eImg);
	int32 GetImageHeight(const ESliderImg eImg);

	CButtonUI & GetLButton() const { return *m_leftButton; }
	CButtonUI & GetRButton() const { return *m_rightButton; }
	
	bool MangeEventButtons(const CEvent * const ev);
private:
	Image * m_barImg;
	Image * m_ballImg;

	CButtonUI * m_leftButton;
	CButtonUI * m_rightButton;
};

#endif //!_C_SLIDER_RENDER_H