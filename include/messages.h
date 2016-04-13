#ifndef _MESSAGES_H
#define _MESSAGES_H

#include "types.h"

enum EEventController;

enum EMessageType {
	EMT_INPUT,
	EMT_SET_POS,
	EMT_SET_ROT,
	EMT_GET_POS,
	EMT_GET_ROT,
	EMT_UPDATE_POS,
	EMT_UPDATE_ROT
};

struct SMessage {
	SMessage(EMessageType type): m_type(type) {}
	virtual ~SMessage() {}
	EMessageType m_type;
};

struct SInputMsg: public SMessage {
	SInputMsg(): SMessage(EMT_INPUT) {}
	SInputMsg(EEventController controller, uint32 id): SMessage(EMT_INPUT),
		m_controller(controller), m_id(id) {}
	EEventController m_controller;
	uint32 m_id;
};

struct SUpdatePosMsg: public SMessage {
	SUpdatePosMsg(): SMessage(EMT_UPDATE_POS) {}
	SUpdatePosMsg(float offsetX, float offsetY): SMessage(EMT_UPDATE_POS),
		m_offsetX(offsetX), m_offsetY(offsetY) {}
	float m_offsetX, m_offsetY;
};

struct SSetPosMsg: public SMessage {
	SSetPosMsg(): SMessage(EMT_SET_POS) {}
	SSetPosMsg(float x, float y): SMessage(EMT_SET_POS),
		m_x(x), m_y(y) {
	}
	float m_x, m_y;
};

struct SUpdateRotMsg: public SMessage {
	SUpdateRotMsg(): SMessage(EMT_UPDATE_ROT) {}
	SUpdateRotMsg(float offsetR): SMessage(EMT_UPDATE_ROT),
		m_offsetRot(offsetR) {
	}
	float m_offsetRot;
};

struct SSetRotMsg: public SMessage {
	SSetRotMsg(): SMessage(EMT_SET_ROT) {}
	SSetRotMsg(float rot): SMessage(EMT_SET_ROT),
		m_rot(rot) {
	}
	float m_rot;
};

struct SGetPosMsg: public SMessage {
	SGetPosMsg(): SMessage(EMT_GET_POS) {}
	void SetPos(float x, float y) {
		m_x = x;
		m_y = y;
		m_modified = true;
	}
	bool Modified() { return m_modified; }
	float m_x, m_y;
private:
	bool m_modified;
};

struct SGetRotMsg: public SMessage {
	SGetRotMsg(): SMessage(EMT_GET_ROT) {}
	void SetRot(float angle) {
		m_angle = angle;
		m_modified = true;
	}
	bool Modified() { return m_modified; }
	float m_angle;
private:
	bool m_modified;
};

//add GetLinearSpeed and GetAngularSpeed messages to use from playerControl

#endif //!_MESSAGES_H