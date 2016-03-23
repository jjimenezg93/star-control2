#pragma warning(push, 0)
#ifndef UGINE_SPRITE_H
#define UGINE_SPRITE_H

#include "renderer.h"
#include "types.h"

class Collision;
class CollisionPixelData;
class Image;
class Map;

class Sprite {
public:
	enum CollisionMode {
		COLLISION_NONE,
		COLLISION_CIRCLE,
		COLLISION_PIXEL,
		COLLISION_RECT
	};

	Sprite(Image* image);
	virtual ~Sprite();

	virtual void SetImage(Image* image);
	virtual const Image* GetImage() const { return m_image; }

	virtual void SetPosition(double x, double y, double z = 0) { m_x = x; m_y = y; m_z = z; }
	virtual void SetX(double x) { m_x = x; }
    virtual void SetY(double y) { m_y = y; }
    virtual void SetZ(double z) { m_z = z; }
	virtual double GetX() const { return m_x; }
    virtual double GetY() const { return m_y; }
    virtual double GetZ() const { return m_z; }
	virtual double GetScreenX() const { return GetX(); }		//isometrica, transformadas en coordenadas de pantalla. por ahora getX m_y getY
    virtual double GetScreenY() const { return GetY(); }

	virtual void SetAngle(double angle) { m_angle = angle; }
	virtual double GetAngle() const { return m_angle; }

	virtual void SetScale(double sx, double sy) { m_scalex = sx; m_scaley = sy; }
	virtual void SetScaleX(double sx) { m_scalex = sx; }
	virtual void SetScaleY(double sy) { m_scaley = sy; }
	virtual double GetScaleX() const { return m_scalex; }
    virtual double GetScaleY() const { return m_scaley; }

	virtual void SetFPS(int16 fps) { m_animFPS = fps; }
	virtual int16 GetFPS() const { return m_animFPS; }
	virtual void SetFrameRange(uint16 firstFrame, uint16 lastFrame) { m_firstFrame = firstFrame; m_lastFrame = lastFrame; m_currentFrame = firstFrame; }
	virtual uint16 GetFirstFrame() const { return m_firstFrame; }
	virtual uint16 GetLastFrame() { return m_lastFrame; }
	virtual void SetCurrentFrame(uint16 frame) { m_currentFrame = frame; }
	virtual uint16 GetCurrentFrame() const { return m_currentFrame; }

	virtual void SetBlendMode(Renderer::BlendMode blend) { m_blendMode = blend; }
	virtual Renderer::BlendMode GetBlendMode() const { return m_blendMode; }
	virtual void SetColor(uint8 r, uint8 g, uint8 b, uint8 alpha = 255) { m_r = r; m_g = g; m_b = b; m_a = alpha; }
	virtual uint8 GetRed() const { return m_r; }
	virtual uint8 GetGreen() const { return m_g; }
	virtual uint8 GetBlue() const { return m_b; }
	virtual uint8 GetAlpha() const { return m_a; }

	virtual void SetRadius(double radius) { m_radius = radius; }
	virtual double GetRadius() const { return m_radius; }

	virtual void SetCollision(CollisionMode mode);
	virtual void SetCollisionPixelData(const CollisionPixelData* colPixelData) { m_colPixelData = colPixelData; }
	virtual const Collision* GetCollision() const { return m_collision; }
    virtual bool CheckCollision(Sprite* sprite);
    virtual bool CheckCollision(const Map* map);
	virtual const Sprite* CollisionSprite() const { return m_colSprite; }
	virtual bool DidCollide() const { return m_collided; }

    virtual void RotateTo(int32 angle, double speed);
    virtual void MoveTo(double x, double y, double speed);
	virtual bool IsRotating() const { return m_rotating; }
	virtual bool IsMoving() const { return m_moving; }

    virtual void Update(double elapsed, const Map* map = NULL);
    virtual void Render() const;
	
	virtual void SetUserData(void* data) { m_userData = data; }
	virtual void* GetUserData() { return m_userData; }
	virtual const void* GetUserData() const { return m_userData; }
protected:
    virtual void UpdateCollisionBox();
    virtual void UpdateCollisionBox(double x, double y, double w, double h);
private:
    Image* m_image;
    double m_x, m_y, m_z;
    double m_colx, m_coly, m_colwidth, m_colheight;
    double m_angle;
    double m_scalex, m_scaley;
    double m_radius;
	double m_centerx, m_centery;		//used to avoid m_col_x and m_coly in circles
    int16 m_animFPS;
    uint16 m_firstFrame, m_lastFrame;
    double m_currentFrame;
    Renderer::BlendMode m_blendMode;
    uint8 m_r, m_g, m_b, m_a;
    Collision* m_collision;
    const CollisionPixelData* m_colPixelData;
    Sprite* m_colSprite;
    bool m_collided;

    bool m_rotating;
    uint16 m_toAngle;
    double m_rotatingSpeed;
    double m_degreesToRotate;

    bool m_moving;
    double m_toX, m_toY;
    double m_movingSpeedX, m_movingSpeedY;
    double m_prevX, m_prevY;
	
	void* m_userData;
};

#endif
#pragma warning(pop)