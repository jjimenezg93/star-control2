#ifndef UGINE_COLLISION_H
#define UGINE_COLLISION_H

class CollisionPixelData;

class Collision {
public:
    virtual bool DoesCollide(const Collision* other) const = 0;									// Colisiones con otras primitivas
    virtual bool DoesCollide(double cx, double cy, double cradius) const = 0;					// Colisiones con un circulo
    virtual bool DoesCollide(double rx, double ry, double rwidth, double rheight) const = 0;	// Colisiones con un rectangulo
    virtual bool DoesCollide(const CollisionPixelData* pixels, double px, double py) const = 0;	// Colisiones con pixeles
};

#endif
