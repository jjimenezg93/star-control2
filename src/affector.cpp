#pragma warning(push, 0)
#include "../include/affector.h"
#include "../include/particle.h"

double genRandomF(double min, double max);

Affector::Affector(double x0, double y0, double x1, double y1) {
	m_x0 = x0;
	m_y0 = y0;
	m_x1 = x1;
	m_y1 = y1;

	m_minr = 0;
	m_ming = 0;
	m_minb = 0;
	m_maxr = 255;
	m_maxg = 255;
	m_maxb = 255;

	m_minangvel = 30;
	m_maxangvel = 360;
}

void Affector::ChangeParticleProperties(Particle &particle) const {
	particle.SetColor(genRandomF(m_minr, m_maxr), genRandomF(m_ming, m_maxg), genRandomF(m_minb, m_maxb), particle.GetAlpha());
	particle.SetVelocityX(genRandomF(m_minvelx, m_maxvelx));
	particle.SetVelocityY(genRandomF(m_minvely, m_maxvely));
	particle.SetAngularVelocity(genRandomF(m_minangvel, m_maxangvel));
	particle.SetAffected(true);
}
#pragma warning(pop)