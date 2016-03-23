//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "../include/app_state.h"
#include "../include/defs.h"
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/filereadstream.h"
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
	stateToDestroy->Deactivate();
	delete stateToDestroy;
}

using namespace rapidjson;

int main() {
	Screen::Instance().Open(1024, 720, false);

	GSetWantedState(EStarControlAS::ESC_START_MENU);

	while (1) {
		if (g_wantedState == ESC_EXIT_APP) {
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
			g_currentAppState->Draw();
		}
	}
	/*FILE* pFile = fopen("data/entities.json", "rb");
	char buffer[65536];
	FileReadStream is(pFile, buffer, sizeof(buffer));
	Document document;
	document.ParseStream<0, UTF8<>, FileReadStream>(is);
	
	if (document.IsObject() && document.HasMember("DreadNought")) {
		std::cout << "Has DreadNought" << std::endl;
	}*/

	
}