#ifndef _APP_STATE_H
#define _APP_STATE_H

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
	virtual void Deactivate() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void ProcessInput() = 0;
};

IAppState * newAppState(EStarControlAS wanted);

#endif //!_APP_STATE_H