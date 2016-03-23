#ifndef UGINE_EMITTER_H
#define UGINE_EMITTER_H

#include "sprite.h"
#include "types.h"

class Affector;
class Particle;

class Emitter {
public:
	Emitter(Image * image, bool autofade);

	virtual void SetPosition(double x, double y) { m_x = x; m_y = y; }
	virtual void SetX(double x) { m_x = x; }
	virtual void SetY(double y) { m_y = y; }
	virtual double GetX() const { return m_x; }
	virtual double GetY() const { return m_y; }

	virtual void SetRate(double minrate, double maxrate) { m_minrate = minrate; m_maxrate = maxrate; }
	virtual void SetVelocityX(double minvelx, double maxvelx) { m_minvelx = minvelx; m_maxvelx = maxvelx; }
	virtual void SetVelocityY(double minvely, double maxvely) { m_minvely = minvely; m_maxvely = maxvely; }
	virtual void SetAngularVelocity(double minangvel, double maxangvel) { m_minangvel = minangvel; m_maxangvel = maxangvel; }
	virtual void SetLifetime(double minlifetime, double maxlifetime) { m_minlifetime = minlifetime; m_maxlifetime = maxlifetime; }
	virtual void SetMinColor(uint8 r, uint8 g, uint8 b) { m_minr = r; m_ming = g; m_minb = b; }
	virtual void SetMaxColor(uint8 r, uint8 g, uint8 b) { m_maxr = r; m_maxg = g; m_maxb = b; }
	virtual void SetBlendMode(Renderer::BlendMode mode = Renderer::BlendMode::ADDITIVE) { m_blendMode = mode; }

	virtual void Start();
	virtual void Stop();
	virtual bool IsEmitting() const { return m_emitting; }

	virtual void AddAffector(const Affector &affector);

	virtual void Update(double elapsed);
	virtual void Render() const;
private:
	Image * m_image;
	bool m_autofade;
	double m_x, m_y;
	double m_minrate, m_maxrate;
	double m_minvelx, m_maxvelx;
	double m_minvely, m_maxvely;
	double m_minangvel, m_maxangvel;
	double m_minlifetime, m_maxlifetime;

	uint8 m_minr, m_ming, m_minb;
	uint8 m_maxr, m_maxg, m_maxb;
	Renderer::BlendMode m_blendMode;
	bool m_emitting;
	Array<Particle> m_particles;
	Array<Affector> m_affectors;
};

#endif //!UGINE_EMITTER_H