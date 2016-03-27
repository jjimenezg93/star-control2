#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

class AudioBuffer;
class AudioStream;

class String;

class AudioSource {
public:
	AudioSource(AudioBuffer* buffer);
	AudioSource(const String &filename);
	~AudioSource();
	unsigned int GetSource() { return m_source; }
	void SetPitch(float pitch);
	void SetGain(float gain);
	void SetLooping(bool loop);
	void SetPosition(float x, float y, float z);
	void SetVelocity(float x, float y, float z);
	void Play();
	void Stop();
	void Pause();
	bool IsPlaying() const;
private:
	unsigned int m_source;
	AudioBuffer * m_buffer;
	AudioStream * m_stream;
};

#endif