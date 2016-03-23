#ifndef UGINE_MAPSCENE_H
#define UGINE_MAPSCENE_H

#include "parallaxscene.h"

class Map;

class MapScene: public ParallaxScene {
public:
	MapScene(Map * map, Image * imageBack = 0, Image * imageFront = 0);
	virtual const Map * GetMap() const { return m_map; }

	virtual void Update(double elapsed);
protected:
	virtual void RenderAfterBackground() const;
private:
	Map * m_map;
};

#endif UGINE_MAPSCENE_H