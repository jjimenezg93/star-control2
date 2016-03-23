#ifndef UGINE_IMAGE_H
#define UGINE_IMAGE_H

#include "string.h"
#include "types.h"

class Image {
public:
    Image(const String& filename, uint16 hframes = 1, uint16 vframes = 1);
	virtual ~Image();

    virtual bool IsValid() const { return m_gltex != 0; }
    virtual const String& GetFilename() const { return m_filename; }
    virtual uint32 GetNumFrames() const { return m_hframes * m_vframes; }
    virtual uint16 GetHFrames() const { return m_hframes; }
    virtual uint16 GetVFrames() const { return m_vframes; }
    virtual uint16 GetWidth() const { return m_width / m_hframes; }
    virtual uint16 GetHeight() const { return m_height / m_vframes; }
    virtual void SetHandle(float handlex, float handley) { m_handlex = handlex; m_handley = handley; }
    virtual void SetMidHandle() { SetHandle(static_cast<float>(GetWidth()/2),
		static_cast<float>(GetHeight()/2)); }
    virtual float GetHandleX() const { return m_handlex; }
    virtual float GetHandleY() const { return m_handley; }
    virtual void Bind() const;
    virtual double GetLastU() const { return m_lastU; }
    virtual double GetLastV() const { return m_lastV; }
protected:
    virtual uint32 GetTexId() const { return m_gltex; }
private:
    String m_filename;
    uint16 m_hframes, m_vframes;
    uint16 m_width, m_height;
	float m_handlex, m_handley;
    uint32 m_gltex;
    double m_lastU, m_lastV;		//image width/buffer width, image height/buffer height
};

#endif
