#pragma warning(push, 0)
#include "..\include\camera.h"
#include "..\include\screen.h"

Camera::Camera() {
	m_x = m_y = 0;
	m_followingSprite = nullptr;
}

void Camera::SetPosition(double x, double y) {
	SetX(x);
	SetY(y);
}

void Camera::SetX(double x) {
	if (x >= m_boundx0 && x <= m_boundx1 - Screen::Instance().GetWidth())
		m_x = x;
	else if (x <= m_boundx0)
		m_x = m_boundx0;
	else if (x >= m_boundx1 - Screen::Instance().GetWidth())
		m_x = m_boundx1;
}

void Camera::SetY(double y) {
	if (y >= m_boundy0 && y <= m_boundy1 - Screen::Instance().GetHeight())
		m_y = y;
	else if (y <= m_boundy0)
		m_y = m_boundy0;
	else if (y >= m_boundy1 - Screen::Instance().GetHeight())
		m_y = m_boundy1;
}

void Camera::SetBounds(double bx0, double by0, double bx1, double by1) {
	m_boundx0 = bx0;
	m_boundy0 = by0;
	m_boundx1 = bx1;
	m_boundy1 = by1;
}

bool Camera::HasBounds() const {
	if (m_boundx0 == m_boundx1)
		return false;
	else
		return true;
}

void Camera::FollowSprite(Sprite * sprite) {
	m_followingSprite = sprite;
}

void Camera::Update() {
	if (m_followingSprite != nullptr) {
		if (HasBounds()) {
			m_x = m_followingSprite->GetX() - Screen::Instance().GetWidth() / 2;
			if (m_x < m_boundx0) {
				m_x = m_boundx0;
			} else if (m_x + Screen::Instance().GetWidth() > m_boundx1) {
				m_x = m_boundx1 - Screen::Instance().GetWidth();
			} else {
				m_x = m_followingSprite->GetX() - Screen::Instance().GetWidth() / 2;
			}

			m_y = m_followingSprite->GetY() - Screen::Instance().GetHeight() / 2;
			if (m_y < m_boundy0) {
				m_y = m_boundy0;
			} else if (m_y + Screen::Instance().GetHeight() > m_boundy1) {
				m_y = m_boundy1 - Screen::Instance().GetHeight();
			} else {
				m_y = m_followingSprite->GetY() - Screen::Instance().GetHeight() / 2;
			}
		} else {
			m_x = m_followingSprite->GetX() - Screen::Instance().GetWidth() / 2;
			m_y = m_followingSprite->GetY() - Screen::Instance().GetHeight() / 2;
		}
	}
}
#pragma warning(pop)