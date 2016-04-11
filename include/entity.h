#ifndef _C_ENTITY_H
#define _C_ENTITY_H

#include "iregistrable.h"
#include "types.h"

#include <vector>

#define ENTITY_NUM_CONTROLS 6

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

	void ReceiveMessage(SMessage * const msg);
	void Update(float elapsed);
	void Render();

	void SetControls(uint16 * controls);

	virtual void Notify(const CEvent * const ev); //IRegistrable
private:
	CComponent * GetComponent(EComponent comp) const;

	std::vector<CComponent *> m_components;

	EGameSide m_side;
	bool m_renderable; //if RemoveComponent() is added ->
						//set this to false when component's type is EC_RENDER

	//up, down, left, right, weapon1, weapon2
	uint16 m_controls[6];
};

#endif //!_C_ENTITY_H