#ifndef _C_WORLD_H
#define _C_WORLD_H

#include "types.h"

#include <vector>

class CEntity;
class Player;
class Scene;

class CWorld {
public:
	CWorld() {} //needed for ASGame default constructor
	~CWorld();

	uint8 Init();

	void Update();
	void Render();
private:
	void DespawnEntity(unsigned int pos);

	std::vector<CEntity *> m_entities;
};

#endif //!_C_WORLD_H