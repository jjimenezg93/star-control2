#pragma warning(push, 0)
#include "../include/parallaxscene.h"
#include "../include/screen.h"

ParallaxScene::ParallaxScene(Image * imageBack, Image * imageFront) {
	m_backLayer = imageBack;
	m_frontLayer = imageFront;
	m_backX = 0;
	m_backY = 0;
	m_frontX = 0;
	m_frontY = 0;
}

void ParallaxScene::Update(double elapsed, Map * map) {
	Scene::Update(elapsed, map);
	m_backX += m_autoBackSpeedX * elapsed;
	m_backY += m_autoBackSpeedY * elapsed;
	m_frontX += m_autoFrontSpeedX * elapsed;
	m_frontY += m_autoFrontSpeedY * elapsed;
}

void ParallaxScene::RenderBackground() const {
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);

	if (m_backLayer != nullptr)
		Renderer::Instance().DrawTiledImage(m_backLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(),
			(GetCamera().GetX() * m_relBackSpeedX) - m_backX, (GetCamera().GetY() * m_relBackSpeedY) - m_backY);
	if (m_frontLayer != nullptr)
		Renderer::Instance().DrawTiledImage(m_frontLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(),
			(GetCamera().GetX() * m_relFrontSpeedX) - m_frontX, (GetCamera().GetY() * m_relFrontSpeedY) - m_frontY);
}
#pragma warning(pop)