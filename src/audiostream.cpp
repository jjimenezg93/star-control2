#pragma warning(push, 0)
#include "../include/audiostream.h"
#include "../include/audiosource.h"
#include "../include/string.h"
#include "AL\al.h"
#include "AL\alc.h"

#define BLOCK_SIZE 32768

Array<AudioStream*> AudioStream::m_streams;

AudioStream::AudioStream(const String & filename, AudioSource * source) {
	m_source = source;
	m_stream = stb_vorbis_open_filename(filename.ToCString(), nullptr, nullptr);
	m_info = stb_vorbis_get_info(m_stream);
	m_samplesLeft = stb_vorbis_stream_length_in_samples(m_stream) * m_info.channels;
	alGenBuffers(2, m_buffers);
	Stream(m_buffers[0]);
	Stream(m_buffers[1]);
	alSourceQueueBuffers(m_source->GetSource(), 2, m_buffers);
	m_streams.Add(this);
}

AudioStream::~AudioStream() {
	for (uint8 i = 0; i < m_streams.Size(); i++) {
		if (m_streams[i] == this) {
			m_streams.RemoveAt(i);
		}
	}
	alDeleteBuffers(2, m_buffers);
	stb_vorbis_close(m_stream);
}

void AudioStream::UpdateAll() {
	for (uint16 i = 0; i < m_streams.Size(); i++) {
		m_streams[i]->Update();
	}
}

void AudioStream::Update() {
	ALint buffersProcessed;
	alGetSourcei(m_source->GetSource(), AL_BUFFERS_PROCESSED, &buffersProcessed);
	ALuint buffer;
	for (uint16 i = 0; i < buffersProcessed; i++) {
		alSourceUnqueueBuffers(m_source->GetSource(), 1, &buffer);
		if (Stream(buffer))
			alSourceQueueBuffers(m_source->GetSource(), 1, &buffer);
		else if (m_shouldLoop) {
			stb_vorbis_seek_start(m_stream);
			m_samplesLeft = stb_vorbis_stream_length_in_samples(m_stream) * m_info.channels;
			if (Stream(buffer))
				alSourceQueueBuffers(m_source->GetSource(), 1, &buffer);
		}
	}
}

bool AudioStream::Stream(unsigned int buffer) {
	int16 pcm[BLOCK_SIZE];		//32KB
	int size = stb_vorbis_get_samples_short_interleaved(m_stream, m_info.channels, pcm, BLOCK_SIZE);
	if (!size) {
		return false;
	}
	ALenum bufferFormat;
	if (m_info.channels == 1)
		bufferFormat = AL_FORMAT_MONO16;
	else
		bufferFormat = AL_FORMAT_STEREO16;
	alBufferData(buffer, bufferFormat, pcm, size * m_info.channels * sizeof(int16), m_info.sample_rate);
	m_samplesLeft - BLOCK_SIZE;
	return true;
}

#pragma warning(pop)