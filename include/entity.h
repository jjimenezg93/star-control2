#ifndef _C_ENTITY_H
#define _C_ENTITY_H

#include <vector>

class CComponent;
enum EComponent;
struct SMessage;

enum EGameSide {
	EGS_PLAYER_1,
	EGS_PLAYER_2
};

enum EEntityType {
	EET_SHIP,
	EET_SHOT
};

class CEntity {
public:
	CEntity(EGameSide side);
	virtual ~CEntity();

	void AddComponent(CComponent * const comp);

	void ReceiveMessage(SMessage * const msg);
	void Update(float elapsed);
	void Render();
private:
	CComponent * GetComponent(EComponent comp) const;

	std::vector<CComponent *> m_components;

	EGameSide m_side;
};

#endif //!_C_ENTITY_H