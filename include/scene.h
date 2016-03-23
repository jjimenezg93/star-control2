#ifndef UGINE_SCENE_H
#define UGINE_SCENE_H

#include "array.h"
#include "camera.h"
#include "types.h"

class Emitter;
class Image;
class Map;
class Sprite;

class Scene {
public:
	enum Layer {
		LAYER_BACK,
		LAYER_MIDDLE,
		LAYER_FRONT,
		LAYER_COUNT
	};

    Scene(Image* backgroundImg = 0);
	virtual ~Scene();

    virtual const Camera& GetCamera() const { return camera; }
    virtual Camera& GetCamera() { return camera; }

    virtual void SetBackgroundImage(Image* image) { this->backgroundImg = image; }
    virtual void SetBackgroundColor(uint8 r, uint8 g, uint8 b) { backr = r; backg = g; backb = b; }

	virtual Sprite* CreateSprite(Image* image, Layer layer = LAYER_BACK);
    virtual void DeleteSprite(Sprite* sprite);

    virtual Emitter* CreateEmitter(Image* image, bool autofade, Layer layer = LAYER_MIDDLE);
    virtual void DeleteEmitter(Emitter* emitter);

    virtual void Update(double elapsed, Map* map = 0);
    virtual void Render() const;
protected:
    virtual void RenderBackground() const {}
    virtual void RenderAfterBackground() const {}
    virtual void RenderSprites(Layer layer) const;
    virtual void RenderEmitters(Layer layer) const;
    virtual void AddSprite(Sprite* sprite, Layer layer) { sprites[layer].Add(sprite); }
    virtual const Array<Sprite*>& GetSprites(Layer layer) const { return sprites[layer]; }
    virtual Array<Sprite*>& GetSprites(Layer layer) { return sprites[layer]; }
private:
    Camera camera;
    uint8 backr, backg, backb;
    Image* backgroundImg;

    Array<Sprite*> sprites[LAYER_COUNT];
    Array<Emitter*> emitters[LAYER_COUNT];
};

#endif
