#ifndef _S_ENTITY_PARAMS_H
#define _S_ENTITY_PARAMS_H

#include <string>

enum EGameSide {
	EGS_PLAYER_1,
	EGS_PLAYER_2
};

struct SEntityParams {
	SEntityParams(std::string shipName, bool isAI, EGameSide side): m_shipName(shipName), m_isAI(isAI),
		m_side(side) {
	}
	std::string m_shipName;
	bool m_isAI;
	EGameSide m_side;
};

#endif //!_S_ENTITY_PARAMS_H