#include "../include/audioengine.h"
#include "AL/al.h"
#include "AL/alc.h"

AudioEngine* AudioEngine::m_engine = nullptr;

AudioEngine& AudioEngine::Instance() {
	if (!m_engine)
		m_engine = new AudioEngine();
	return *m_engine;
}

void AudioEngine::Init() {
	m_device = alcOpenDevice(nullptr);
	m_context = alcCreateContext((ALCdevice *)m_device, nullptr);
	alcMakeContextCurrent((ALCcontext *)m_context);
}

void AudioEngine::Finish() {
	if (m_device)
		alcDestroyContext((ALCcontext *)m_context);
	if (m_context)
		alcCloseDevice((ALCdevice *)m_device);
}

void AudioEngine::SetDopplerFactor(float factor) {
	alDopplerFactor(factor);
}

AudioEngine::~AudioEngine(void) {
	delete m_engine;
}
