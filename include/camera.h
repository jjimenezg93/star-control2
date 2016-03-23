#ifndef UGINE_CAMERA_H
#define UGINE_CAMERA_H

#include "sprite.h"

class Camera {
public:
	Camera();

	virtual void SetPosition(double x, double y);
	virtual void SetX(double x);
	virtual void SetY(double y);
	virtual double GetX() const { return m_x; };
	virtual double GetY() const { return m_y; };

	virtual void SetBounds(double bx0, double by0, double bx1, double by1);
	virtual bool HasBounds() const;
	virtual double GetMinX() const { return m_boundx0; };
	virtual double GetMinY() const { return m_boundy0; };
	virtual double GetMaxX() const { return m_boundx1; };
	virtual double GetMaxY() const { return m_boundy1; };
	
	virtual void FollowSprite(Sprite* sprite);

	virtual void Update();
private:
	double m_x, m_y;
	double m_boundx0, m_boundy0, m_boundx1, m_boundy1;
	Sprite * m_followingSprite;
};

#endif