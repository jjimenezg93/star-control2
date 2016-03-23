#ifndef UGINE_COLLISIONMANAGER_H
#define UGINE_COLLISIONMANAGER_H

class CollisionPixelData;

class CollisionManager {
public:
	static const CollisionManager & Instance();

	virtual bool CircleToCircle(double x1, double y1, double r1,
		double x2, double y2, double r2) const;

	virtual bool CircleToPixels(double cx, double cy, double cr,
		const CollisionPixelData* pixels, double px, double py) const;

	virtual bool CircleToRect(double cx, double cy, double cr,
		double rx, double ry, double rw, double rh) const;

	virtual bool PixelsToPixels(const CollisionPixelData* p1, double x1, double y1,
		const CollisionPixelData* p2, double x2, double y2) const;

	virtual bool PixelsToRect(const CollisionPixelData* pixels, double px, double py,
		double rx, double ry, double rw, double rh) const;

	virtual bool RectToRect(double x1, double y1, double w1, double h1,
		double x2, double y2, double w2, double h2) const;
protected:
	CollisionManager() {}
	virtual ~CollisionManager() {}
private:
	static CollisionManager * m_manager;
};

#endif