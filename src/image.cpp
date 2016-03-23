#pragma warning(push, 0)
#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>
#include "../include/renderer.h"

extern "C" {
	unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
	void stbi_image_free(void *retval_from_stbi_load);
}

Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	m_filename = filename;
	m_hframes = hframes;
	m_vframes = vframes;
	m_width = 0;
	m_height = 0;
	m_handlex = 0;
	m_handley = 0;
	m_gltex = 0;
	m_lastU = 1.0;
	m_lastV = 1.0;

	int width32 = 0;
	int height32 = 0;
	int * ptrComp = NULL;

	uint8 *buffer = stbi_load(filename.ToCString(), &width32, &height32, ptrComp, 4);

	m_width = static_cast<uint16>(width32);
	m_height = static_cast<uint16>(height32);

	//PO2 -> Power of 2
	double widthPO2 = pow(2, ceil(Log2(m_width)));
	double heightPO2 = pow(2, ceil(Log2(m_height)));

	if (widthPO2 != m_width || heightPO2 != m_height) {
		m_lastU = static_cast<double>(m_width / widthPO2);
		m_lastV = static_cast<double>(m_height / heightPO2);

		widthPO2 = static_cast<uint16>(widthPO2);
		heightPO2 = static_cast<uint16>(heightPO2);

		//allocating memory for new buffer
		uint8 * bufferPO2 = (uint8 *)malloc(widthPO2 * heightPO2 * 4);		// * 4 because each pixel needs 32 bits

		uint8 * const origBufferPO2pos = bufferPO2;		//ptr to keep reference to the bufferPO2
		uint8 * const origBufferpos = buffer;

		//setting pixels to white -> as texture has transparent pixels, check everything is working properly
		memset(bufferPO2, 0, widthPO2 * heightPO2 * 4);

		for (unsigned int h = 0; h < m_height; h++) {
			memcpy(bufferPO2, buffer, m_width * 4);
			bufferPO2 += static_cast<int>(widthPO2) * 4;
			buffer += (m_width * 4);
		}

		bufferPO2 = origBufferPO2pos;
		buffer = origBufferpos;

		//call to genImage, creating texture in VRAM
		m_gltex = Renderer::Instance().GenImage(bufferPO2, widthPO2, heightPO2);

		//now, the texture is in VRAM so we no longer need it in RAM
		stbi_image_free(bufferPO2);

		if (buffer)
			stbi_image_free(buffer);
	} else {
		// Generamos la textura
		if (buffer) {
			m_gltex = Renderer::Instance().GenImage(buffer, m_width, m_height);
			stbi_image_free(buffer);
		}
	}
}

Image::~Image() {
	if (m_gltex != 0) Renderer::Instance().DeleteImage(m_gltex);
}

void Image::Bind() const {
	Renderer::Instance().BindImage(m_gltex);
}
#pragma warning(pop)