#include <iostream>

#include "../include/app_state.h"
#include "../include/as_start_menu.h"
#include "../include/as_game_conf_menu.h"
#include "../include/as_end_game.h"
#include "../include/as_game.h"

uint16 IAppState::m_currentFrames = 0;
clock_t IAppState::m_framesTimer = 0;
clock_t IAppState::m_lastTimer = 0;

IAppState * newAppState(EStarControlAS wanted) {
	switch (wanted) {
	case ESC_NULL:
		return nullptr;
		break;
	case ESC_START_MENU:
		return new ASStartMenu();
		break;
	case ESC_GAME_CONF_MENU:
		return new ASGameConfMenu();
		break;
	case ESC_GAME:
		return new ASGame();
		break;
	case ESC_END_GAME:
		return new ASEndGameMenu();
		break;
	case ESC_EXIT_APP:
		return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
}

void IAppState::Render() {
	m_framesTimer = clock();
	float duration = (static_cast<float>(m_framesTimer - m_lastTimer))
		/ CLOCKS_PER_SEC;
	if (duration > 1.f) {
		system("cls");
		std::cout << "frames = " << m_currentFrames << std::endl;
		m_currentFrames = 0;
		m_lastTimer = clock();
		m_framesTimer = m_lastTimer;
	} else {
		m_currentFrames++;
	}
}