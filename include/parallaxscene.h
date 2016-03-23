#ifndef UGINE_PARALLAXSCENE_H
#define UGINE_PARALLAXSCENE_H

#include "image.h"
#include "scene.h"

class ParallaxScene : public Scene {
public:
	ParallaxScene(Image * imageBack, Image * imageFront = 0);

	virtual const Image * GetBackLayer() const { return m_backLayer; }
	virtual const Image * GetFrontLayer() const { return m_frontLayer; }

	virtual void SetRelativeBackSpeed(double x, double y) { m_relBackSpeedX = x, m_relBackSpeedY = y; }
	virtual void SetRelativeFrontSpeed(double x, double y) { m_relFrontSpeedX = x, m_relFrontSpeedY = y; }
	virtual void SetAutoBackSpeed(double x, double y) { m_autoBackSpeedX = x, m_autoBackSpeedY = y; }
	virtual void SetAutoFrontSpeed(double x, double y) { m_autoFrontSpeedX = x, m_autoFrontSpeedY = y; }

	virtual void Update(double elapsed, Map * map = 0);
protected:
	virtual void RenderBackground() const;
private:
	Image * m_backLayer;
	Image * m_frontLayer;
	double m_backX, m_backY;
	double m_frontX, m_frontY;
	double m_relBackSpeedX, m_relBackSpeedY;
	double m_relFrontSpeedX, m_relFrontSpeedY;
	double m_autoBackSpeedX, m_autoBackSpeedY;
	double m_autoFrontSpeedX, m_autoFrontSpeedY;
};

#endif //!UGINE_PARALLAXSCENE_H