#ifndef _C_ENTITY_H
#define _C_ENTITY_H

#include "iregistrable.h"
#include "types.h"

#include <vector>

class CComponent;
class CCompRender;
class CWorld;
enum EComponent;
enum EEntityType;
enum EGameSide;
struct SMessage;

class CEntity: public IRegistrable {
public:
	CEntity(EGameSide side, CWorld * world, bool renderable = false);
	virtual ~CEntity();

	bool IsRenderable() const { return m_renderable; }
	EGameSide GetSide() const { return m_side; }
	EEntityType GetType();

	void AddComponent(CComponent * comp);
	
	CCompRender * GetRenderComp() const { return m_renderComp; }
	void IsCollision(CEntity * other);

	void Update(float elapsed);
	void Render();

	virtual void Notify(const CEvent * const ev); //IRegistrable
	void ReceiveMessage(SMessage &msg);
private:
	CComponent * GetComponent(EComponent comp) const;

	std::vector<CComponent *> m_components;

	CWorld * m_world;
	EGameSide m_side;

	bool m_renderable; //if RemoveComponent() is added ->
						//set this to false when component's type is EC_RENDER
	CCompRender * m_renderComp;
};

#endif //!_C_ENTITY_H