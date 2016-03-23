#ifndef UGINE_SKELETONSPRITE_H
#define UGINE_SKELETONSPRITE_H

#include "sprite.h"
#include "string.h"

class Bone;
class Map;

class SkeletonSprite : public Sprite {
public:
    SkeletonSprite(const String& filename);
    virtual ~SkeletonSprite();

    virtual const Bone* GetRootBone() const { return root; }

	virtual void Update(double elapsed, Map* map = NULL);
    virtual void Render() const;
protected:
    virtual void UpdateCollisionBox() { Sprite::UpdateCollisionBox(0, 0, 0, 0); }
private:
    Bone* root;
};

#endif
