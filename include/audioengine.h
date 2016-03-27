#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

class AudioEngine {
public:
	static AudioEngine& Instance();
	void Init();
	void Finish();

	void SetDopplerFactor(float factor);
protected:
	AudioEngine(void) : m_device(nullptr), m_context(nullptr) {}
	~AudioEngine(void);
private:
	static AudioEngine* m_engine;
	void* m_device;
	void* m_context;
};

#endif