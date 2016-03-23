#pragma warning(push, 0)
#include "../include/particle.h"

Particle::Particle(): Sprite(nullptr) {
	m_affected = false;
}

Particle::Particle(Image * image, double velx, double vely, double angularVel, double lifetime, bool autofade): Sprite(image) {
	m_velocityx = velx;
	m_velocityy = vely;
	m_angularVelocity = angularVel;
	m_initialLifetime = lifetime;
	m_lifetime = lifetime;
	m_autofade = autofade;
	m_affected = false;
	SetBlendMode(Renderer::BlendMode::ADDITIVE);
}

void Particle::Update(double elapsed) {
	SetPosition(GetX() + (m_velocityx * elapsed), GetY() + (m_velocityy * elapsed));
	SetAngle(GetAngle() + m_angularVelocity * elapsed);
	short int newAlpha = GetAlpha();
	if (m_autofade) {
		double fadingRate = 255 / m_initialLifetime;
		newAlpha -= fadingRate * elapsed;
		if (newAlpha < 0)
			SetColor(GetRed(), GetGreen(), GetBlue(), 0);
		else
			SetColor(GetRed(), GetGreen(), GetBlue(), newAlpha);
	}
	m_lifetime -= elapsed;
}
#pragma warning(pop)