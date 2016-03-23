#ifndef UGINE_PIXELCOLLISION_H
#define UGINE_PIXELCOLLISION_H

#include "collision.h"
#include "collisionmanager.h"

class PixelCollision : public Collision {
public:
	PixelCollision(double* x, double* y, const CollisionPixelData* colData) : m_x(x), m_y(y), m_colData(colData) {}

	virtual bool DoesCollide(const Collision* other) const { return other->DoesCollide(m_colData, *m_x, *m_y); }
	virtual bool DoesCollide(double cx, double cy, double cradius) const { return CollisionManager::Instance().CircleToPixels(cx, cy, cradius, m_colData, *m_x, *m_y); }
	virtual bool DoesCollide(double rx, double ry, double rwidth, double rheight) const { return CollisionManager::Instance().PixelsToRect(m_colData, *m_x, *m_y, rx, ry, rwidth, rheight); }
	virtual bool DoesCollide(const CollisionPixelData* pixels, double px, double py) const { return CollisionManager::Instance().PixelsToPixels(m_colData, *m_x, *m_y, pixels, px, py); }
private:
	double* m_x;
	double* m_y;
	const CollisionPixelData * m_colData;
};

#endif //!UGINE_PIXELCOLLISION_H
