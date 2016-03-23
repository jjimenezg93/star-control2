#ifndef UGINE_FONT_H
#define UGINE_FONT_H

#include "glyph.h"
#include "image.h"
#include "string.h"		//includes array.h
#include "types.h"

class Font : public Image {
public:
	Font(const String &filename);

	virtual uint16 GetSize() const;
	virtual uint32 GetTextWidth(const String &text) const;
	virtual uint32 GetTextHeight(const String &text) const;

	virtual float GetX() const { return m_x; }
	virtual float GetY() const { return m_y; }
	virtual double GetSpeedX() const { return m_speedX; }
	virtual double GetSpeedY() const { return m_speedY; }
	virtual void SetX(float x) { m_x = x; }
	virtual void SetY(float y) { m_y = y; }
	virtual void SetSpeedX(double speedX) { m_speedX = speedX; }
	virtual void SetSpeedY(double speedY) { m_speedY = speedY; }

	virtual void Render(const String &text, double x, double y) const;
private:
	float m_x, m_y;
	double m_speedX, m_speedY;

	Array<Glyph> glyphs;
};

#endif