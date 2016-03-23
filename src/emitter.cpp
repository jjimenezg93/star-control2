#pragma warning(push, 0)
#include <ctime>

#include "../include/affector.h"
#include "../include/array.h"
#include "../include/emitter.h"
#include "../include/particle.h"

double genRandomF(double min, double max) {
	return ((double(rand()) / double(RAND_MAX)) * (max - min) + min);
}

Emitter::Emitter(Image * image, bool autofade) {
	m_image = image;
	m_autofade = autofade;
	m_emitting = false;
}

void Emitter::Start() {
	srand(static_cast<unsigned int>(time(nullptr)));
	m_emitting = true;
}

void Emitter::Stop() {
	m_emitting = false;
}

void Emitter::AddAffector(const Affector &affector) {
	m_affectors.Add(affector);
}

void Emitter::Update(double elapsed) {
	if (m_emitting) {
		double randVelX;
		double randVelY;
		double randAngVel;
		double randLifetime;
		double randRate = genRandomF(m_minrate, m_maxrate) * elapsed;

		//spawn
		uint8 randR, randG, randB;
		Particle p;
		for (unsigned short int i = 0; i < randRate; i++) {
			randVelX = genRandomF(m_minvelx, m_maxvelx);
			randVelY = genRandomF(m_minvely, m_maxvely);
			randAngVel = genRandomF(m_minangvel, m_maxangvel);
			randLifetime = genRandomF(m_minlifetime, m_maxlifetime);
			randR = genRandomF(m_minr, m_maxr);
			randG = genRandomF(m_ming, m_maxg);
			randB = genRandomF(m_minb, m_maxb);
			p = Particle(m_image, randVelX, randVelY, randAngVel, randLifetime, m_autofade);
			p.SetBlendMode(Renderer::BlendMode::ADDITIVE);
			p.SetColor(randR, randG, randB);
			p.SetPosition(m_x, m_y);
			m_particles.Add(p);
		}
	}
	//update
	for (unsigned short int i = 0; i < m_particles.Size(); i++) {
		if (!m_particles[i].Affected()) {
			for (unsigned short int j = 0; j < m_affectors.Size(); j++) {
				if (m_particles[i].GetX() >= m_affectors[j].GetX0() && m_particles[i].GetX() <= m_affectors[j].GetX1()
					&& m_particles[i].GetY() >= m_affectors[j].GetY0() && m_particles[i].GetY() <= m_affectors[j].GetY1()) {
					m_affectors[j].ChangeParticleProperties(m_particles[i]);
				}
			}
		}
		if (m_particles[i].GetAlpha() == 0 || m_particles[i].GetLifeTime() <= 0) {
			m_particles.RemoveAt(i);
		} else
			m_particles[i].Update(elapsed);
	}
}

void Emitter::Render() const {
	for (unsigned short int i = 0; i < m_particles.Size(); i++) {
		Renderer::Instance().SetBlendMode(m_particles[i].GetBlendMode());
		m_particles[i].Render();
	}
}
#pragma warning(pop)