#include "../include/collisionpixeldata.h"
#include "../include/u-gine.h"

extern "C" {
	unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
	void stbi_image_free(void *retval_from_stbi_load);
}

CollisionPixelData::CollisionPixelData(const String & filename) {
	m_filename = filename;

	int width32 = 0;
	int height32 = 0;
	int * ptrComp = NULL;

	uint8 * buffer = stbi_load(filename.ToCString(), &width32, &height32, ptrComp, 4);
	uint8 * ptrBuffer = buffer;

	m_width = static_cast<uint16>(width32);
	m_height = static_cast<uint16>(height32);

	uint32 numPixels = m_width * m_height;
	bool * bufferBool = (bool *)malloc(numPixels);
	m_data = bufferBool;

	for (uint32 i = 0; i < numPixels; i++) {
		if (*((uint32 *)(ptrBuffer)) == 0xff000000)
			*bufferBool = true;
		else
			*bufferBool = false;
		bufferBool++;
		ptrBuffer+=4;
	}

	if (buffer)
		stbi_image_free(buffer);
}

CollisionPixelData::~CollisionPixelData() {
	delete m_data;
}

bool CollisionPixelData::GetData(uint32 x, uint32 y) const {
	bool * ptrBuffer = m_data;
	return ptrBuffer[(m_width * y) + x];
}
