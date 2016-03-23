#pragma warning(push, 0)
#include "../include/glyph.h"

Glyph::Glyph(double ox, double oy, double ex, double ey) {
	m_origX = ox;
	m_origY = oy;
	m_endX = ex;
	m_endY = ey;
}
#pragma warning(pop)