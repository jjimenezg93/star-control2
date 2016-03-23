#ifndef UGINE_CIRCLECOLLISION_H
#define UGINE_CIRCLECOLLISION_H

#include "collision.h"
#include "collisionmanager.h"

class CircleCollision : public Collision {
public:
    CircleCollision(double* x, double* y, double* radius) : x(x), y(y), radius(radius) {}

    virtual bool DoesCollide(const Collision* other) const { return other->DoesCollide(*x, *y, *radius); }
    virtual bool DoesCollide(double cx, double cy, double cradius) const { return CollisionManager::Instance().CircleToCircle(*x, *y, *radius, cx, cy, cradius); }
    virtual bool DoesCollide(double rx, double ry, double rwidth, double rheight) const { return CollisionManager::Instance().CircleToRect(*x, *y, *radius, rx, ry, rwidth, rheight); }
    virtual bool DoesCollide(const CollisionPixelData* pixels, double px, double py) const { return CollisionManager::Instance().CircleToPixels(*x, *y, *radius, pixels, px, py); }
private:
    double* x;
    double* y;
    double* radius;
};

#endif
