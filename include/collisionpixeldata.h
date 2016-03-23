#ifndef UGINE_COLLISIONPIXELDATA_H
#define UGINE_COLLISIONPIXELDATA_H

#include "types.h"
#include "string.h"

class CollisionPixelData {
public:
	CollisionPixelData(const String& filename);
	virtual ~CollisionPixelData();
	virtual bool IsValid() const { return m_data != nullptr; }
	virtual const String& GetFilename() const { return m_filename; }
	virtual uint16 GetWidth() const { return m_width; }
	virtual uint16 GetHeight() const { return m_height; }
	virtual bool GetData(uint32 x, uint32 y) const;
private:
	String m_filename;
	uint16 m_width, m_height;
	bool * m_data;
};

#endif //!UGINE_COLLISIONPIXELDATA_H
