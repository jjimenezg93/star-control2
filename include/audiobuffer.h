#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

class String;

class AudioBuffer {
public:
	AudioBuffer(const String& filename);
	~AudioBuffer(void);
	bool IsValid() const { return m_alBuffer != 0; }
	unsigned int GetBuffer() const { return m_alBuffer; }
private:
	unsigned int m_alBuffer;
};

#endif