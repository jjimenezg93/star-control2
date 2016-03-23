#ifndef _DEFS_H
#define _DEFS_H

class IAppState;
class Game;
enum EStarControlAS;

extern IAppState * g_currentAppState;
extern EStarControlAS g_wantedState;
extern Game * g_game;

extern void GSetWantedState(EStarControlAS newState);

#endif //!_DEFS_H