#pragma warning(push, 0)
#include "../include/resourcemanager.h"
#include "../include/collisionpixeldata.h"
#include "../include/font.h"
#include "../include/image.h"
//#include "../include/isometricmap.h"
#include "../include/map.h"

ResourceManager* ResourceManager::manager = NULL;

ResourceManager::~ResourceManager() {
	FreeResources();
}

ResourceManager& ResourceManager::Instance() {
	if ( !manager )
		manager = new ResourceManager();
	return *manager;
}

CollisionPixelData* ResourceManager::LoadCollisionPixelData(const String& filename) {
    // Comprobamos si esta cargado
    for ( uint32 i = 0; i < collisionPixelDatas.Size(); i++ )
        if ( collisionPixelDatas[i]->GetFilename() == filename )
            return collisionPixelDatas[i];

    // Cargamos
    CollisionPixelData* cp = new CollisionPixelData(filename);
    if ( cp->IsValid() ) {
        collisionPixelDatas.Add(cp);
        return cp;
    } else {
        delete cp;
        return NULL;
    }
}

Font* ResourceManager::LoadFont(const String &filename) {
	// Comprobamos si esta cargada
    for ( uint32 i = 0; i < fonts.Size(); i++ )
        if ( fonts[i]->GetFilename() == filename )
            return fonts[i];

	// Cargamos
	Font* font = new Font(filename);
	if ( font->IsValid() ) {
        fonts.Add(font);
		return font;
	} else {
		delete font;
		return NULL;
	}
}


Image* ResourceManager::LoadImage(const String &filename, uint16 hframes, uint16 vframes) {
	// Comprobamos si esta cargada
    for ( uint32 i = 0; i < images.Size(); i++ )
        if ( images[i]->GetFilename() == filename )
            return images[i];

	// Cargamos
	Image* image = new Image(filename, hframes, vframes);
	if ( image->IsValid() ) {
        images.Add(image);
		return image;
	} else {
		delete image;
		return NULL;
	}
}

Map* ResourceManager::LoadMap(const String &filename, uint16 firstColId) {
	// Comprobamos si esta cargado
    for ( uint32 i = 0; i < maps.Size(); i++ )
        if ( maps[i]->GetFilename() == filename )
            return maps[i];

	// Cargamos
	Map* map = new Map(filename, firstColId);
	if ( map->IsValid() ) {
        maps.Add(map);
		return map;
	} else {
		delete map;
		return NULL;
	}
}
/*
IsometricMap* ResourceManager::LoadIsometricMap(const String &filename, uint16 firstColId) {
	// Comprobamos si esta cargado
    for ( uint32 i = 0; i < isometricMaps.Size(); i++ )
        if ( isometricMaps[i]->GetFilename() == filename )
            return isometricMaps[i];

	// Cargamos
	IsometricMap* isometricMap = new IsometricMap(filename, firstColId);
	if ( isometricMap->IsValid() ) {
        isometricMaps.Add(isometricMap);
		return isometricMap;
	} else {
		delete isometricMap;
		return NULL;
	}
}
*/
void ResourceManager::FreeFonts() {
    for ( uint32 i = 0; i < fonts.Size(); i++ )
        delete fonts[i];
    fonts.Clear();
}


void ResourceManager::FreeImages() {
    for ( uint32 i = 0; i < images.Size(); i++ )
        delete images[i];
    images.Clear();
}

void ResourceManager::FreeCollisionPixelDatas() {
    for ( uint32 i = 0; i < collisionPixelDatas.Size(); i++ )
        delete collisionPixelDatas[i];
    collisionPixelDatas.Clear();
}

void ResourceManager::FreeMaps() {
    for ( uint32 i = 0; i < maps.Size(); i++ )
        delete maps[i];
    maps.Clear();
}
/*
void ResourceManager::FreeIsometricMaps() {
    for ( uint32 i = 0; i < isometricMaps.Size(); i++ )
        delete isometricMaps[i];
    isometricMaps.Clear();
}
*/

void ResourceManager::FreeResources() {
	FreeCollisionPixelDatas();
	FreeFonts();
	FreeImages();
	FreeMaps();
	//FreeIsometricMaps();
}
#pragma warning(pop)