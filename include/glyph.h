#ifndef UGINE_GLYPH_H
#define UGINE_GLYPH_H

class Glyph {
public:
	Glyph() {}
	Glyph(double ox, double oy, double ex, double ey);

	virtual float GetOrigX() const { return m_origX; }
	virtual float GetOrigY() const { return m_origY; }
	virtual void SetOrigX(float x) { m_origX = x; }
	virtual void SetOrigY(float y) { m_origY = y; }

	virtual float GetEndX() const { return m_endX; }
	virtual float GetEndY() const { return m_endY; }
	virtual void SetEndX(float x) { m_endX = x; }
	virtual void SetEndY(float y) { m_endY = y; }
private:
	double m_origX, m_origY, m_endX, m_endY;
};

#endif