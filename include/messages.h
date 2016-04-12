#ifndef _MESSAGES_H
#define _MESSAGES_H

#include "types.h"

enum EEventController;

enum EMessageType {
	EMT_INPUT,
	EMT_UPDATE_POS,
};

struct SMessage {
	SMessage(EMessageType type): m_type(type) {}
	virtual ~SMessage() {}
	EMessageType m_type;
};

struct SInputMessage: public SMessage {
	SInputMessage(): SMessage(EMT_INPUT) {}
	SInputMessage(EEventController controller, uint32 id): SMessage(EMT_INPUT),
		m_controller(controller), m_id(id) {}
	EEventController m_controller;
	uint32 m_id;
};

struct SUpdatePosMessage: public SMessage {
	SUpdatePosMessage(): SMessage(EMT_UPDATE_POS) {}
	SUpdatePosMessage(float offsetX, float offsetY): SMessage(EMT_UPDATE_POS),
		m_offsetX(offsetX), m_offsetY(offsetY) {}
	float m_offsetX, m_offsetY;
};

#endif //!_MESSAGES_H