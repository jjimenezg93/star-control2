#pragma warning(push, 0)
#include "../include/map.h"
#include "../include/mapscene.h"
#include "../include/parallaxscene.h"

MapScene::MapScene(Map * map, Image * imageBack, Image * imageFront): ParallaxScene(imageBack, imageFront) {
	m_map = map;
}

void MapScene::Update(double elapsed) {
	ParallaxScene::Update(elapsed, m_map);
}

void MapScene::RenderAfterBackground() const{
	m_map->Render();
}
#pragma warning(pop)