#ifndef _C_ENTITY_H
#define _C_ENTITY_H

#include <vector>

class CComponent;
enum EGameSide {
	EGS_PLAYER_1,
	EGS_PLAYER_2
};
struct SMessage;

class CEntity {
public:
	CEntity(EGameSide side);
	virtual ~CEntity();

	void AddComponent(CComponent * const comp);

	void ReceiveMessage(SMessage * const msg);
	virtual void Update(float elapsed);
private:
	std::vector<CComponent *> m_components;

	EGameSide m_side;
};

#endif //!_C_ENTITY_H