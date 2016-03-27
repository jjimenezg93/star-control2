#ifndef AUDIOSTREAM_H
#define AUDIOSTREAM_H

#include "../include/array.h"

#define STB_VORBIS_HEADER_ONLY
#include "../lib/stb_vorbis.c"

class String;
class AudioSource;

class AudioStream {
public:
	AudioStream(const String& filename, AudioSource* source);
	~AudioStream();
	void SetLooping(bool looping) { m_shouldLoop = looping; }
	static void UpdateAll();
protected:
	void Update();
	bool Stream(unsigned int buffer);
private:
	static Array<AudioStream*> m_streams;
	AudioSource* m_source;
	stb_vorbis* m_stream;
	stb_vorbis_info m_info;
	unsigned int m_buffers[2];
	size_t m_samplesLeft;
	bool m_shouldLoop;
};

#endif //!AUDIOSTREAM_H