#ifndef _MESSAGES_H
#define _MESSAGES_H

enum EDodgerPlayerControlKey {
	EDPC_LEFT,
	EDPC_RIGHT,
	EDPC_UP,
	EDPC_DOWN
};

class Sprite;

struct SMessage {
	virtual ~SMessage() {}
};

struct GetSpritePosMessage: public SMessage {
	GetSpritePosMessage(bool modif = false) {
		m_modified = modif;
	}
	float m_x, m_y;
	bool m_modified;
};

struct GetSpriteMessage: public SMessage {
	GetSpriteMessage(Sprite * sp, bool modif = false) {
		m_sprt = sp;
		m_modified = modif;
	}
	Sprite * m_sprt;
	bool m_modified;
};

struct IsCollisionMessage: public SMessage {
	IsCollisionMessage(CEntity * const et) {
		m_entity = et;
		m_collided = false;
	}
	CEntity * m_entity;
	bool m_collided;
};


struct ChangeMovementDirection: public SMessage {
	ChangeMovementDirection(bool changeX, bool changeY) {
		m_changeX = changeX;
		m_changeY = changeY;
	}
	bool m_changeX, m_changeY;
};

struct PlayerControlMessage: public SMessage {
	PlayerControlMessage(EDodgerPlayerControlKey key, float elapsed) {
		m_key = key;
		m_elapsed = elapsed;
	}
	EDodgerPlayerControlKey m_key;
	float m_elapsed;
};

//if there is a way to set the Sprite, we need this message to be called from CComponentRender
struct UpdateSpriteMessage: public SMessage {
	UpdateSpriteMessage(Sprite * const sp) {
		m_sprt = sp;
	}
	Sprite * m_sprt;
};

struct UpdateSpritePosMessage: public SMessage {
	UpdateSpritePosMessage(float x, float y) { m_x = x; m_y = y; }
	float m_x, m_y;
};

struct UpdateComponentPosMessage: public SMessage {
	UpdateComponentPosMessage(float x, float y, float elapsed) { //used as a relative update
		m_x = x;
		m_y = y;
		m_elapsed = elapsed;
	}
	float m_x, m_y, m_elapsed;
};

#endif //!_MESSAGES_H