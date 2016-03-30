#ifndef _C_WORLD_H
#define _C_WORLD_H

#include "../include/string.h"

#include <vector>

class CEntity;
class Player;
class Scene;

class CWorld {
public:
	CWorld(const String background);
	~CWorld();

	void Run();
	void Draw();

	CEntity * GetPlayer() { return m_player; }
private:
	void DespawnEntity(unsigned int pos);

	Scene * m_scene;
	std::vector<CEntity *> m_entities;
	CEntity * m_player; //makes collision detection easier
};

#endif //!_C_WORLD_H