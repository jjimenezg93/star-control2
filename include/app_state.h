#ifndef _APP_STATE_H
#define _APP_STATE_H

#include <ctime>
#include <chrono>

#include "../include/types.h"

//AS = AppState
enum EStarControlAS {
	ESC_NULL,
	ESC_START_MENU,
	ESC_GAME_CONF_MENU,
	ESC_GAME,
	ESC_END_GAME,
	ESC_EXIT_APP
};

class IAppState {
public:
	virtual ~IAppState() {};

	virtual void Init() = 0;
	virtual void Update() = 0;
	//framerate counter
	virtual void Render();
	virtual void ProcessInput() {}
	uint16 GetCurrentFrames() const { return m_currentFrames; }
protected:
private:
	static uint16 m_currentFrames;
	static clock_t m_framesTimer;
	static clock_t m_lastTimer;
};

IAppState * newAppState(EStarControlAS wanted);

#endif //!_APP_STATE_H