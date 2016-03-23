#include "../include/sprite.h"
#include "../include/rectcollision.h"
#include "../include/image.h"
#include "../include/map.h"
#include "../include/math.h"
#include "../include/pixelcollision.h"
#include "../include/renderer.h"
#include "../include/circlecollision.h"
#include "../include/screen.h"
#include <math.h>
#pragma warning(push, 0)

Sprite::Sprite(Image* image) {
	m_image = image;
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_colx = 0;
	m_coly = 0;
	m_colwidth = m_image->GetWidth();
	m_colheight = m_image->GetHeight();
	m_angle = 0;
	m_scalex = 1;
	m_scaley = 1;
	if (m_image->GetHeight() > m_image->GetWidth())
		m_radius = m_image->GetHeight() / 2;
	else
		m_radius = m_image->GetWidth() / 2;
	m_centerx = m_colx + m_radius;
	m_centery = m_coly + m_radius;
	m_animFPS = 0;
	m_firstFrame = 0;
	m_lastFrame = 1;
	m_currentFrame = m_firstFrame;
	m_blendMode = Renderer::BlendMode::ALPHA;
	m_r = 255;
	m_g = 255;
	m_b = 255;
	m_a = 255;
	m_collision = nullptr;
	m_colPixelData = nullptr;
	m_colSprite = nullptr;
	m_collided = false;

	m_rotating = false;
	m_toAngle = 0;
	m_rotatingSpeed = 0;
	m_degreesToRotate = 0;

	m_moving = false;
	m_toX = m_x;
	m_toY = m_y;
	m_movingSpeedX = 0;
	m_movingSpeedY = 0;
	m_prevX = m_x;
	m_prevY = m_y;

	m_userData = nullptr;
}

Sprite::~Sprite() {
	if (m_collision)
		delete m_collision;
}

void Sprite::SetImage(Image* image) {
	m_image = image;
	if (m_image->GetHeight() > m_image->GetWidth())
		m_radius = m_image->GetHeight() / 2;
	else
		m_radius = m_image->GetWidth() / 2;
}

void Sprite::SetCollision(CollisionMode mode) {
	if (m_collision)
		delete m_collision;
	switch (mode) {
	case COLLISION_NONE:
		m_collision = nullptr;
		break;
	case COLLISION_CIRCLE:
		m_collision = new CircleCollision(&m_centerx, &m_centery, &m_radius);
		break;
	case COLLISION_RECT:
		m_collision = new RectCollision(&m_colx, &m_coly, &m_colwidth, &m_colheight);
		break;
	case COLLISION_PIXEL:
		m_collision = new PixelCollision(&m_colx, &m_coly, m_colPixelData);
	default:
		break;
	}
}

bool Sprite::CheckCollision(Sprite* sprite) {
	if (m_collision && sprite->m_collision) {
		if (m_collision->DoesCollide(sprite->GetCollision())) {
			m_colSprite = sprite;
			m_collided = true;
			sprite->m_colSprite = this;
			sprite->m_collided = true;
			return true;
		} else
			return false;
	} else
		return false;
}

bool Sprite::CheckCollision(const Map* map) {
	if (m_collision) {
		if (map->CheckCollision(m_collision)) {
			m_collided = true;
			return true;
		}
	}
	return false;
}

void Sprite::RotateTo(int32 angle, double speed) {
	double wrapAngle = WrapValue(angle, 360);

	if (WrapValue(angle, 360) == WrapValue(m_angle, 360) || speed == 0)
		m_rotating = false;
	else {
		m_rotating = true;
		double cw = WrapValue(m_angle - wrapAngle, 360);
		double ccw = WrapValue(wrapAngle - m_angle, 360);
		if (min(ccw, cw) == ccw) {
			m_degreesToRotate = ccw;
			m_toAngle = wrapAngle;
			m_rotatingSpeed = abs(speed);
		} else {
			m_degreesToRotate = cw;
			m_toAngle = wrapAngle;
			m_rotatingSpeed = -abs(speed);
		}
	}
}

void Sprite::MoveTo(double x, double y, double speed) {
	if (round(x) == round(m_x) && round(y) == round(m_y) || speed == 0) {
		m_moving = false;
	} else {
		m_toX = x;
		m_toY = y;
		m_moving = true;
		double time = sqrt(pow(m_toX - m_x, 2) + pow(m_toY - m_y, 2)) / speed;
		if (time == 0 && m_toX == 0)
			m_movingSpeedX = 0;
		else
			m_movingSpeedX = (m_toX - m_x) / time;
		if (time == 0 && m_toY == 0)
			m_movingSpeedY = 0;
		else
			m_movingSpeedY = (m_toY - m_y) / time;
	}
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	m_colSprite = NULL;
	m_collided = false;

	m_currentFrame += m_animFPS * elapsed;
	
	if (m_currentFrame >= m_lastFrame) {
		m_currentFrame = m_firstFrame;
	}

	if (m_currentFrame < m_firstFrame) {
		m_currentFrame = m_lastFrame;
	}

	//rotation update
	if (m_rotating == true) {
		double r = m_rotatingSpeed * elapsed;
		m_degreesToRotate -= abs(r);
		SetAngle(GetAngle() + r);

		if (m_degreesToRotate <= 0) {
			m_rotating = false;
			SetAngle(m_toAngle);
		}
	}

	//move update
	if (m_moving == true) {
		double moveX = m_x + (m_movingSpeedX * elapsed);
		double moveY = m_y + (m_movingSpeedY * elapsed);

		m_prevX = m_x;
		m_prevY = m_y;

		SetX(moveX);
		UpdateCollisionBox();
		if (CheckCollision(map)) {
			SetX(m_prevX);
		}
		
		SetY(moveY);
		UpdateCollisionBox();
		if (CheckCollision(map)) {
			SetY(m_prevY);
		}

		if (m_prevX == m_x && m_prevY == m_y) {
			MoveTo(m_x, m_y, 0);
			m_moving = false;
		}

		if (m_movingSpeedX <= 0 && m_x <= m_toX) {
			m_moving = false;
		} else if (m_movingSpeedX >= 0 && m_x >= m_toX) {
			m_moving = false;
		}

		if (m_movingSpeedY <= 0 && m_y <= m_toY) {
			m_moving = false;
		} else if (m_movingSpeedY >= 0 && m_y >= m_toY) {
			m_moving = false;
		}
	}

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
	Renderer::Instance().SetBlendMode(m_blendMode);

	Renderer::Instance().SetColor(m_r, m_g, m_b, m_a);

	Renderer::Instance().DrawImage(m_image, m_x, m_y, m_currentFrame, m_image->GetWidth() * m_scalex, m_image->GetHeight() * m_scaley, m_angle);

	//fix: this way color only affects this sprite
	Renderer::Instance().SetColor(255, 255, 255, 255); 
}

void Sprite::UpdateCollisionBox() {
	m_colx = m_x - m_image->GetHandleX() * fabs(m_scalex);
	m_coly = m_y - m_image->GetHandleY() * fabs(m_scaley);
	m_colwidth = m_image->GetWidth() * fabs(m_scalex);
	m_colheight = m_image->GetHeight() * fabs(m_scaley);
	m_centerx = m_colx + m_image->GetHandleX() * fabs(m_scalex);
	m_centery = m_coly + m_image->GetHandleY() * fabs(m_scaley);
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	m_colx = x;
	m_coly = y;
	m_colwidth = w;
	m_colheight = h;
	m_centerx = x + (w / 2);
	m_centery = y + (h / 2);
}
#pragma warning(pop)