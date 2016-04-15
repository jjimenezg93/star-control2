//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "../include/app_state.h"
#include "../include/defs.h"
#include "../include/u-gine.h"

#include <assert.h>
#include <iostream>

IAppState * g_currentAppState;
EStarControlAS g_wantedState;
Game * g_game;

EStarControlAS g_currentMenuOp;

void GSetWantedState(EStarControlAS newState) {
	g_wantedState = newState;
}

void DestroyState(IAppState *stateToDestroy) {
	delete stateToDestroy;
}

int main() {
	Screen::Instance().Open(800, 600, false);

	GSetWantedState(EStarControlAS::ESC_START_MENU);
#pragma warning(disable: 4127)
	while (1) {
#pragma warning(default: 4127)
		if (g_wantedState == ESC_EXIT_APP) {
			DestroyState(g_currentAppState);
			break;
		} else if (g_wantedState != ESC_NULL) {
			if (g_currentAppState) {
				DestroyState(g_currentAppState);
			}
			g_currentAppState = newAppState(g_wantedState);
			if (g_currentAppState) {
				g_currentAppState->Init();
			}

			GSetWantedState(ESC_NULL); //critical
		}

		if (g_currentAppState != nullptr) {
			g_currentAppState->ProcessInput();
			g_currentAppState->Update();
			g_currentAppState->Render();
		}
	}
}