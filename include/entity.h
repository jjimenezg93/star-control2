#ifndef _C_ENTITY_H
#define _C_ENTITY_H

#include "iregistrable.h"
#include "types.h"

#include <vector>

class CComponent;
enum EComponent;
enum EGameSide;
struct SMessage;

enum EEntityType {
	EET_SHIP,
	EET_SHOT
};

class CEntity: public IRegistrable {
public:
	CEntity(EGameSide side, bool renderable = false);
	virtual ~CEntity();

	bool IsRenderable() const { return m_renderable; }

	void AddComponent(CComponent * const comp);

	void Update(float elapsed);
	void Render();

	virtual void Notify(const CEvent * const ev); //IRegistrable
	void ReceiveMessage(SMessage &msg);
private:
	CComponent * GetComponent(EComponent comp) const;

	std::vector<CComponent *> m_components;

	EGameSide m_side;
	bool m_renderable; //if RemoveComponent() is added ->
						//set this to false when component's type is EC_RENDER
};

#endif //!_C_ENTITY_H