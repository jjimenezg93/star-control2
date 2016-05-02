#ifndef _DEFS_H
#define _DEFS_H

#include <vector>

class IAppState;
class Game;
class CEntity;
enum EStarControlAS;
enum EGameSide;
struct SEntityParams;

extern std::vector<SEntityParams *> g_entitiesParams;
extern int8 g_winner; //-1 = no winner, 0 = player1, 1 = player2.

extern IAppState * g_currentAppState;
extern EStarControlAS g_wantedState;
extern Game * g_game;

extern void GSetWantedState(EStarControlAS newState);

#endif //!_DEFS_H