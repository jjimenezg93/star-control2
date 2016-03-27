#pragma warning(push, 0)
#include "../include/listener.h"
#include "AL\al.h"
#include "AL\alc.h"

Listener * Listener::m_listener = nullptr;

Listener & Listener::Instance() {
	if(!m_listener)
		m_listener = new Listener();
	return *m_listener;
}

void Listener::SetPosition(float x, float y, float z) {
	alListener3f(AL_POSITION, x, y, z);
}

void Listener::SetVelocity(float x, float y, float z) {
	alListener3f(AL_VELOCITY, x, y, z);
}

void Listener::SetOrientation(float x, float y, float z) {
	alListener3f(AL_ORIENTATION, x, y, z);
}

Listener::Listener() {
	SetPosition(0, 0, 0);
	SetOrientation(0, 0, 0);
	SetVelocity(0, 0, 0);
}

Listener::~Listener() {
	delete m_listener;
}

#pragma warning(pop)