#include "../include/app_state.h"
#include "../include/as_start_menu.h"

IAppState * newAppState(EStarControlAS wanted) {
	switch (wanted) {
	case ESC_NULL:
		return nullptr;
		break;
	case ESC_START_MENU:
		return new ASStartMenu();
		break;
	case ESC_GAME_CONF_MENU:
		break;
	case ESC_GAME:
		break;
	case ESC_END_GAME:
		break;
	case ESC_EXIT_APP:
		return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
}