#pragma warning(push, 0)
#include "../include/map.h"
#include "../include/rectcollision.h"
#include "../include/collision.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"
#include <limits.h>

using namespace rapidxml;

Map::Map(const String &filename, uint16 firstColId) {
	m_filename = filename;
	m_firstColId = firstColId;
	m_valid = false;

	String buffer = String::Read(filename);

	if (buffer != "") {
		xml_document<> doc;
		doc.parse<0>((char *)buffer.ToCString());
		xml_node<> * rootNode = doc.first_node("map");
		
		m_width = String(rootNode->first_attribute("width")->value()).ToInt();
		m_height = atof(rootNode->first_attribute("height")->value());
		m_tileWidth = atof(rootNode->first_attribute("tilewidth")->value());
		m_tileHeight = atof(rootNode->first_attribute("tileheight")->value());

		xml_node<> * tilesetNode = rootNode->first_node("tileset");			//ignoring other tilesets if any, only getting the first one
		int firstGID = String(tilesetNode->first_attribute("firstgid")->value()).ToInt();
		int tileWidth = String(tilesetNode->first_attribute("tilewidth")->value()).ToInt();
		int tileHeight = String(tilesetNode->first_attribute("tileheight")->value()).ToInt();
		int tileOffsetX = 0;
		int tileOffsetY = 0;
		if (tilesetNode->first_node("tileoffset")) {
			tileOffsetX = String(tilesetNode->first_node("tileoffset")->first_attribute("x")->value()).ToInt();
			tileOffsetY = String(tilesetNode->first_node("tileoffset")->first_attribute("y")->value()).ToInt();
		}
		
		xml_node<> * imageNode = tilesetNode->first_node("image");
		m_imageFile = String(imageNode->first_attribute("source")->value()).StripDir();
		int imageWidth = String(imageNode->first_attribute("width")->value()).ToInt();
		int imageHeight = String(imageNode->first_attribute("height")->value()).ToInt();
		//delete imageNode;

		xml_node<> * dataNode = rootNode->first_node("layer")->first_node("data");
		if (!dataNode->first_attribute("encoding")
			&& !dataNode->first_attribute("compression")) {
			xml_node<> * tileNode = dataNode->first_node("tile");
			while (tileNode != NULL) {
				int32 tileId = String(tileNode->first_attribute("gid")->value()).ToInt() - firstGID;
				m_tileIds.Add(tileId);
				tileNode = tileNode->next_sibling("tile");
			}
			String tilesetFile = filename.ExtractDir() + "/" + m_imageFile;
			m_image = ResourceManager::Instance().LoadImage(tilesetFile,
				imageWidth / tileWidth, imageHeight / tileHeight);
			m_image->SetHandle(tileOffsetX, tileOffsetY);

			m_valid = true;
		}
	}
}

void Map::Render() const {
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= 0 ) {
				Renderer::Instance().DrawImage(m_image, x*GetTileWidth(), y*GetTileHeight(), GetTileId(x, y));
			}
		}
	}
}

bool Map::CheckCollision(const Collision* collision) const {
	// Creamos caja de colisiones
	double boxX = 0, boxY = 0, boxWidth = GetTileWidth(), boxHeight = GetTileHeight();
	RectCollision boxCol(&boxX, &boxY, &boxWidth, &boxHeight);
	
	// Comprobamos colision con cada tile
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= m_firstColId ) {
				boxX = x * GetTileWidth();
				boxY = y * GetTileHeight();

				if ( collision->DoesCollide(&boxCol) )
					return true;
			}
		}
	}

	return false;
}

double Map::GetGroundY(double x, double y) const {
	double groundY = UINT_MAX;

	if ( x < 0  ||  x >= m_width*m_tileWidth  ||  y >= m_height*m_tileHeight ) return groundY;
	if ( y < 0 ) y = 0;

	// Buscamos el primer tile en esa columna
	for ( int tiley = int(y/m_tileHeight); tiley < m_height; tiley++ ) {
		if ( m_tileIds[tiley*m_width + int(x/m_tileWidth)] >= 0 ) {
			groundY = tiley*m_tileHeight;
			break;
		}
	}
	return groundY;
}
#pragma warning(pop)