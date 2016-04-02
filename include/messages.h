#ifndef _MESSAGES_H
#define _MESSAGES_H

enum EMessageType {

};

struct SMessage {
	virtual ~SMessage() {}
	EMessageType m_type;
};



#endif //!_MESSAGES_H