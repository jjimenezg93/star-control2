#pragma warning(push, 0)
#include "..\include\font.h"
#include "..\include\renderer.h"
#include "..\include\resourcemanager.h"

extern "C" {
	unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
	void stbi_image_free(void *retval_from_stbi_load);
}

Font::Font(const String &filename) : Image(filename, 16, 16) {
	m_x = 0;
	m_y = 0;
	m_speedX = 0;
	m_speedY = 0;

	for (unsigned short int f = 0; f < GetNumFrames(); f++)
		glyphs.Add(Glyph(0, 0, GetWidth(), GetHeight()));

	int width32 = 0;
	int height32 = 0;
	int *ptrComp = nullptr;
	
	uint8 * const buffer = stbi_load(filename.ToCString(), &width32, &height32, ptrComp, 4);	//this pointer should never be missing
	
	if (buffer) {
		uint8 *ptrBuffer = buffer;

		//0x<A><B><G><R>
		const uint32 red = 0xff0000ff;
		const uint32 yellow = 0xff00ffff;
		const uint32 black = 0xff000000;
		const uint32 transparent = 0x00000000;

		unsigned short int i, j;
		uint16 row = 0;
		uint16 col = 0;

		for (unsigned short int frame = 0; frame < GetNumFrames(); frame++) {
			row = frame / GetHFrames();
			col = frame % GetHFrames();
			ptrBuffer = buffer + ((GetWidth() * col) * 4) + (row * GetHeight() * GetWidth() * GetHFrames() * 4);
			for (j = 0; j < GetHeight(); j++) {
				for (i = 0; i < GetWidth(); i++) {
					//inside each frame
					if (*((uint32 *)(ptrBuffer)) == black)
						memset(ptrBuffer, transparent, 4);
					else if (*((uint32 *)(ptrBuffer)) == yellow) {
						glyphs[frame].SetOrigX(i);
						glyphs[frame].SetOrigY(j);
						memset(ptrBuffer, transparent, 4);
					} else if (*((uint32 *)(ptrBuffer)) == red) {
						glyphs[frame].SetEndX(i);
						glyphs[frame].SetEndY(j);
						memset(ptrBuffer, transparent, 4);
					}
					ptrBuffer += 4;
				}
				ptrBuffer += ((GetHFrames() * GetWidth()) - GetWidth()) * 4;
			}
		}
		Renderer::Instance().GenFontImage(buffer, width32, height32);
		delete buffer;
	}
}

uint16 Font::GetSize() const {
	return GetHeight();
}

uint32 Font::GetTextWidth(const String & text) const {
	uint32 toRet = 0;
	const char * str = text.ToCString();

	//glyphs[*str] -> frame position corresponds to char ASCII code
	while (*str != '\0') {
		toRet += glyphs[*str].GetEndX() - glyphs[*str].GetOrigX();
		str++;
	}
	return toRet;
}

uint32 Font::GetTextHeight(const String & text) const {
	uint32 toRet = 0;
	uint32 height;
	const char * str = text.ToCString();

	while (*str != '\0') {
		height = glyphs[*str].GetEndY() - glyphs[*str].GetOrigY();
		if (height > toRet)
			toRet = height;
		str++;
	}
	return toRet;
}

void Font::Render(const String & text, double x, double y) const{
	/* ASCII
	* 32 = (space)
	* 48 = 0
	* 64 = @
	* 65 = A
	* 126 = ~		<- last
	*/

	const char * str = text.ToCString();
	unsigned short int offset = 0;

	while (*str != '\0') {
		Renderer::Instance().DrawImage(this, x + offset, y, *str, GetHeight(), GetWidth(), 0);

		offset += glyphs[*str].GetEndX() - glyphs[*str].GetOrigX();
		str++;
	}
}
#pragma warning(pop)