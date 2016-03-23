#ifndef UGINE_SKELETONDATA_H
#define UGINE_SKELETONDATA_H

#include "array.h"
#include "bonedata.h"
#include "string.h"
#include "types.h"

class SkeletonData {
public:
    SkeletonData(const String& filename);
    virtual ~SkeletonData() {}

    virtual const Array<BoneData>& GetBoneDatas() const { return boneDatas; }
private:
    Array<BoneData> boneDatas;
};

#endif
