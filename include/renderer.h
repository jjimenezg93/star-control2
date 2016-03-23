#ifndef UGINE_RENDERER_H
#define UGINE_RENDERER_H

#include "string.h"
#include "types.h"

class Font;
class Image;

class Renderer {
public:
    enum BlendMode {
		SOLID,
		ALPHA,
		MULTIPLICATIVE,
		ADDITIVE
	};

    static const Renderer& Instance() { if ( !renderer ) renderer = new Renderer(); return *renderer; }

    virtual void SetBlendMode(BlendMode blendMode) const;
    virtual void SetColor(uint8 r, uint8 g, uint8 b, uint8 a) const;
    virtual void SetOrigin(double x, double y) const;
    virtual void Clear(uint8 r = 0, uint8 g = 0, uint8 b = 0) const;
    virtual void DrawPoint(double x, double y) const;
    virtual void DrawLine(double x1, double y1, double x2, double y2) const;
    virtual void DrawRect(double x, double y, double width, double height) const;
    virtual void DrawEllipse(double x, double y, double xradius, double yradius) const;
    virtual void DrawImage(const Image* image, double x, double y, uint32 frame = 0, double width = 0.0f, double height = 0.0f, double ang = 0) const;
    virtual void DrawTiledImage(const Image* image, double x, double y, double width, double height, double offsetx = 0, double offsety = 0) const;
	virtual void DrawText(const Font* font, const String& text, double x, double y) const;

	uint32 GenImage(uint8* buffer, uint16 width, uint16 height) const;
	void GenFontImage(uint8 * buffer, uint16 width, uint16 height) const;
	void BindImage(uint32 glhandle) const;
	void DeleteImage(uint32 glhandle) const;

	virtual void PushMatrix() const;
	void PopMatrix() const;
	void TranslateMatrix(double x, double y, double z) const;
	void RotateMatrix(double rotation, double x, double y, double z) const;
	void ScaleMatrix(double x, double y, double z) const;

protected:
    Renderer() {}
private:
    static Renderer* renderer;
};

#endif
