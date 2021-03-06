#ifndef _COMP_PLAYER_CONTROL_H
#define _COMP_PLAYER_CONTROL_H

#include "component.h"
#include "types.h"

const uint16 kEntityNumControls = 6;
const uint16 kPosUpdateOffset = 5;
const float kRotationRate = 5;

struct SMessage;

class CCompPlayerControl: public CComponent {
public:
	CCompPlayerControl(CEntity * et);
	~CCompPlayerControl();

	virtual void ReceiveMessage(SMessage &msg);
	virtual void Update(float elapsed);

	void SetControls(uint16 controls[kEntityNumControls]);
private:
	bool GetLinearOffset(float &offsetX, float &offsetY) const;

	void MoveUp(float elapsed);
	void MoveDown(float elapsed);
	void TurnLeft(float elapsed);
	void TurnRight(float elapsed);
	void Shoot(uint8 weaponId);

	//up, down, left, right, weapon1, weapon2
	uint16 m_controls[kEntityNumControls];
};

#endif //!_COMP_PLAYER_CONTROL_H