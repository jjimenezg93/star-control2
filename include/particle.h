#ifndef UGINE_PARTICLE_H
#define UGINE_PARTICLE_H

#include "sprite.h"
#include "types.h"

class Particle : public Sprite {
public:
	Particle();
	Particle(Image * image, double velx, double vely, double angularVel, double lifetime, bool autofade);

	virtual double GetLifeTime() const { return m_lifetime; }

	virtual void SetVelocityX(double velx) { m_velocityx = velx; }
	virtual void SetVelocityY(double vely) { m_velocityy = vely; }

	virtual void SetAngularVelocity(double angVel) { m_angularVelocity = angVel; }

	virtual bool Affected() const { return m_affected; }
	virtual void SetAffected(bool affected) { m_affected = affected; }

	virtual void Update(double elapsed);
private:
	double m_velocityx, m_velocityy;
	double m_angularVelocity;
	double m_lifetime;
	double m_initialLifetime;
	bool m_autofade;
	bool m_affected;
};

#endif //!UGINE_PARTICLE_H