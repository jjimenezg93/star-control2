#ifndef _S_ENTITY_PARAMS_H
#define _S_ENTITY_PARAMS_H

#include "string.h"

enum EGameSide {
	EGS_PLAYER_1,
	EGS_PLAYER_2
};

struct SEntityParams {
	SEntityParams(String name, bool isAI, EGameSide side): m_name(name), m_isAI(isAI),
		m_side(side) {
	}
	String m_name;
	bool m_isAI;
	EGameSide m_side;
};

#endif //!_S_ENTITY_PARAMS_H