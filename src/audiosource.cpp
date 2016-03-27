#include "../include/audiosource.h"
#include "../include/audiobuffer.h"
#include "../include/audiostream.h"
#include "AL\al.h"
#include "AL\alc.h"

AudioSource::AudioSource(AudioBuffer * buffer) {
	alGenSources(1, &m_source);
	m_buffer = buffer;
	m_stream = nullptr;
	SetPitch(1);
	SetGain(1);
	SetLooping(false);
	SetPosition(0, 0, 0);
	SetVelocity(0, 0, 0);
	alSourcei(m_source, AL_BUFFER, buffer->GetBuffer());
}

AudioSource::AudioSource(const String &filename) {
	m_stream = new AudioStream(filename, this);
	alGenSources(1, &m_source);
	m_buffer = nullptr;
	SetPitch(1);
	SetGain(1);
	SetLooping(false);
	SetPosition(0, 0, 0);
	SetVelocity(0, 0, 0);
}

AudioSource::~AudioSource() {
	alDeleteSources(1, &m_source);
}

void AudioSource::SetPitch(float pitch) {
	alSourcef(m_source, AL_PITCH, pitch);
}

void AudioSource::SetGain(float gain) {
	alSourcef(m_source, AL_GAIN, gain);
}

void AudioSource::SetLooping(bool loop) {
	if (!m_stream)
		alSourcei(m_source, AL_LOOPING, loop);
	else
		m_stream->SetLooping(loop);
}

void AudioSource::SetPosition(float x, float y, float z) {
	alSource3f(m_source, AL_POSITION, x, y, z);
}

void AudioSource::SetVelocity(float x, float y, float z) {
	alSource3f(m_source, AL_VELOCITY, x, y, z);
}

void AudioSource::Play() {
	alSourcePlay(m_source);
}

void AudioSource::Stop() {
	alSourceStop(m_source);
}

void AudioSource::Pause() {
	alSourcePause(m_source);
}

bool AudioSource::IsPlaying() const {
	ALint state;
	alGetSourcei(m_source, AL_SOURCE_STATE, &state);
	if (state == AL_PLAYING)
		return true;
	return false;
}