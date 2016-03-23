#ifndef UGINE_RESOURCEMANAGER_H
#define UGINE_RESOURCEMANAGER_H

#include "array.h"
#include "string.h"
#include "types.h"

class CollisionPixelData;
class Font;
class Image;
class IsometricMap;
class Map;

class ResourceManager {
public:
    static ResourceManager& Instance();

    virtual CollisionPixelData* LoadCollisionPixelData(const String& filename);
    virtual Font* LoadFont(const String& filename);
    virtual Image* LoadImage(const String& filename, uint16 hframes = 1, uint16 vframes = 1);
    virtual Map* LoadMap(const String& filename, uint16 firstColId = 0);
    //virtual IsometricMap* LoadIsometricMap(const String& filename, uint16 firstColId = 0);
    virtual void FreeCollisionPixelDatas();
    virtual void FreeFonts();
    virtual void FreeImages();
    virtual void FreeMaps();
    //virtual void FreeIsometricMaps();
    virtual void FreeResources();
protected:
    ResourceManager() {}
    virtual ~ResourceManager();
private:
    static ResourceManager* manager;

    Array<CollisionPixelData*> collisionPixelDatas;
    Array<Font*> fonts;
    Array<Image*> images;
    Array<Map*> maps;
    //Array<IsometricMap*> isometricMaps;
};

#endif
