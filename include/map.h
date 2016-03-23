#ifndef UGINE_MAP_H
#define UGINE_MAP_H

#include "array.h"
#include "string.h"
#include "types.h"

class Collision;
class Image;

class Map {
public:
    Map(const String& filename, uint16 firstColId = 0);

    virtual const String& GetFilename() const { return m_filename; }
    virtual bool IsValid() const { return m_valid; }
    virtual void Render() const;
    virtual bool CheckCollision(const Collision* collision) const;
    virtual const Image* GetImage() const { return m_image; }
    virtual Image* GetImage() { return m_image; }
    virtual uint32 GetWidth() const { return m_width * m_tileWidth; }
    virtual uint32 GetHeight() const { return m_height * m_tileHeight; }
    virtual uint16 GetTileWidth() const { return m_tileWidth; }
    virtual uint16 GetTileHeight() const { return m_tileHeight; }
    virtual uint16 GetColumns() const { return m_width; }
    virtual uint16 GetRows() const { return m_height; }
    virtual int32 GetTileId(uint16 column, uint16 row) const { return m_tileIds[row*GetColumns() + column]; }
    virtual double GetGroundY(double x, double y) const;
    virtual uint16 GetFirstColId() const { return m_firstColId; }
private:
    bool m_valid;
    String m_filename;
    uint16 m_width, m_height;
    uint16 m_tileWidth, m_tileHeight;
    String m_imageFile;
    Image* m_image;
    Array<int32> m_tileIds;
    uint16 m_firstColId;
};

#endif
