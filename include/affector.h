#ifndef UGINE_AFFECTOR_H
#define UGINE_AFFECTOR_H

#include "types.h"

class Particle;

class Affector {
public:
	Affector() {}
	Affector(double x0, double y0, double x1, double y1);

	virtual void SetZone(double x0, double y0, double x1, double y1) { m_x0 = x0; m_y0 = y0; m_x1 = x1; m_y1 = y1; }
	virtual void SetX0(double x) { m_x0 = x; }
	virtual void SetY0(double y) { m_y0 = y; }
	virtual void SetX1(double x) { m_x1 = x; }
	virtual void SetY1(double y) { m_y1 = y; }
	virtual double GetX0() const { return m_x0; }
	virtual double GetY0() const { return m_y0; }
	virtual double GetX1() const { return m_x1; }
	virtual double GetY1() const { return m_y1; }

	virtual void SetMinColor(uint8 r, uint8 g, uint8 b) { m_minr = r; m_ming = g; m_minb = b; }
	virtual void SetMaxColor(uint8 r, uint8 g, uint8 b) { m_maxr = r; m_maxg = g; m_maxb = b; }

	virtual void SetVelocityX(double minvelx, double maxvelx) { m_minvelx = minvelx; m_maxvelx = maxvelx; }
	virtual void SetVelocityY(double minvely, double maxvely) { m_minvely = minvely; m_maxvely = maxvely; }
	virtual void SetAngularVelocity(double minangvel, double maxangvel) { m_minangvel = minangvel; m_maxangvel = maxangvel; }

	virtual void ChangeParticleProperties(Particle &part) const;
private:
	double m_x0, m_y0, m_x1, m_y1;

	uint8 m_minr, m_ming, m_minb;
	uint8 m_maxr, m_maxg, m_maxb;

	double m_minvelx, m_maxvelx;
	double m_minvely, m_maxvely;
	double m_minangvel, m_maxangvel;
};

#endif //!UGINE_AFFECTOR_H