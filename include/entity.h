#ifndef _C_ENTITY_H
#define _C_ENTITY_H

#include <vector>

class CComponent;
enum EDodgerEntityType;
struct SMessage;

class CEntity {
public:
	CEntity();
	virtual ~CEntity();

	virtual EDodgerEntityType GetType() const { return m_type; }
	virtual void SetType(const EDodgerEntityType newType) { m_type = newType; } //not in use atm

	void AddComponent(CComponent * const comp);

	void ReceiveMessage(SMessage * const msg);
	virtual void Update(float elapsed);
private:
	std::vector<CComponent *> m_components;

	EDodgerEntityType m_type;
};

#endif //!_C_ENTITY_H