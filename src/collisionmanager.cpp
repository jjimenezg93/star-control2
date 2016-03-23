#pragma warning(push, 0)
#define _USE_MATH_DEFINES

#include "../include/collisionmanager.h"
#include "../include/collisionpixeldata.h"
#include "../include/math.h"
#include <cmath>

CollisionManager * CollisionManager::m_manager = nullptr;

const CollisionManager & CollisionManager::Instance()
{
	if (!m_manager)
		m_manager = new CollisionManager();
	return *m_manager;
}

bool CollisionManager::CircleToCircle(double x1, double y1, double r1, double x2, double y2, double r2) const {
	if (Distance(x1, y1, x2, y2) < r1 + r2)
		return true;
	else return false;
}

bool CollisionManager::CircleToPixels(double cx, double cy, double cr, const CollisionPixelData * pixels, double px, double py) const {
	if (RectsOverlap(cx - cr, cy - cr, cr * 2, cr * 2, px, py, pixels->GetWidth(), pixels->GetHeight())) {
		double overlapX, overlapY, overlapWidth, overlapHeight;
		OverlappingRect(cx - cr, cy - cr, cr * 2, cr * 2, px, py, pixels->GetWidth(), pixels->GetHeight(), &overlapX, &overlapY, &overlapWidth, &overlapHeight);
		double offY = overlapY - py;
		double offX;
		while (offY < overlapHeight + overlapY - py) {
			offX = overlapX - px;
			while (offX < overlapWidth + overlapX - px) {
				if (pixels->GetData(offX, offY) && Distance(cx, cy, offX + px, offY + py) <= cr)
					return true;
				offX++;
			}
			offY++;
		}
	}
	return false;
}

bool CollisionManager::CircleToRect(double cx, double cy, double cr, double rx, double ry, double rw, double rh) const {
	if (PointInRect(cx, cy, rx, ry, rw, rh))
		return true;
	else {
		double nearestX;
		double nearestY;
		ClosestPointToRect(cx, cy, rx, ry, rw, rh, &nearestX, &nearestY);

		if (Distance(cx, cy, nearestX, nearestY) <= cr)
			return true;
		else
			return false;
	}
}

bool CollisionManager::PixelsToPixels(const CollisionPixelData * p1, double x1, double y1, const CollisionPixelData * p2, double x2, double y2) const {
	if (RectsOverlap(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight())) {
		double overlapX, overlapY, overlapWidth, overlapHeight;
		OverlappingRect(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight(), &overlapX, &overlapY, &overlapWidth, &overlapHeight);
		double py1 = overlapY - y1;
		double py2 = overlapY - y2;
		double px1, px2;
		while (py1 < overlapHeight + overlapY - y1 && py2 < overlapHeight + overlapY - y2) {
			px1 = overlapX - x1;
			px2 = overlapX - x2;
			while (px1 < overlapWidth + overlapX - x1 && px2 < overlapWidth + overlapX - x2) {
				if (p1->GetData(px1, py1) && p2->GetData(px2, py2)) {
					return true;
				}
				px1++;
				px2++;
			}
			py1++;
			py2++;
		}
	}
	return false;
}

bool CollisionManager::PixelsToRect(const CollisionPixelData * pixels, double px, double py, double rx, double ry, double rw, double rh) const {
	if (RectsOverlap(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry , rw, rh)) {
		double overlapX, overlapY, overlapWidth, overlapHeight;
		OverlappingRect(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh, &overlapX, &overlapY, &overlapWidth, &overlapHeight);
		double offsetY = overlapY - py;
		double offsetX;
		while (offsetY < overlapHeight + overlapY - py) {
			offsetX = overlapX - px;
			while (offsetX < overlapWidth + overlapX - px) {
				if (pixels->GetData(offsetX, offsetY))
					return true;
				offsetX++;
			}
			offsetY++;
		}
	}

	return false;
}

bool CollisionManager::RectToRect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) const {
	if (RectsOverlap(x1, y1, w1, h1, x2, y2, w2, h2))
		return true;
	else
		return false;
}
#pragma warning(pop)