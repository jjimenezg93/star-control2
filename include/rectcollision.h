#ifndef UGINE_RECTCOLLISION_H
#define UGINE_RECTCOLLISION_H

#include "collision.h"
#include "collisionmanager.h"

class RectCollision : public Collision {
public:
    RectCollision(double* x, double* y, double* width, double* height) : x(x), y(y), width(width), height(height) {}

    virtual bool DoesCollide(const Collision* other) const { return other->DoesCollide(*x, *y, *width, *height); }
    virtual bool DoesCollide(double cx, double cy, double cradius) const { return CollisionManager::Instance().CircleToRect(cx, cy, cradius, *x, *y, *width, *height); }
    virtual bool DoesCollide(double rx, double ry, double rwidth, double rheight) const { return CollisionManager::Instance().RectToRect(*x, *y, *this->width, *this->height, rx, ry, rwidth, rheight); }
    virtual bool DoesCollide(const CollisionPixelData* pixels, double px, double py) const { return CollisionManager::Instance().PixelsToRect(pixels, px, py, *x, *y, *width, *height); }
private:
    double* x;
    double* y;
    double* width;
    double* height;
};

#endif
