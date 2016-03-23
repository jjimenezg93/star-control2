#ifndef UGINE_FRAME_H
#define UGINE_FRAME_H

#include "types.h"

class Frame {
public:
    Frame() : id(0), translationx(0), translationy(0), rotation(0), scalex(1), scaley(1) {}
    Frame(int32 id, double translationx, double translationy, double rotation, double scalex, double scaley);
    virtual int32 GetId() const { return id; }
    virtual double GetTranslationX() const { return translationx; }
    virtual double GetTranslationY() const { return translationy; }
    virtual double GetRotation() const { return rotation; }
    virtual double GetScaleX() const { return scalex; }
    virtual double GetScaleY() const { return scaley; }
private:
    int32 id;
    double translationx, translationy;
    double rotation;
    double scalex, scaley;
};

inline Frame::Frame(int32 id, double translationx, double translationy, double rotation, double scalex, double scaley)
    : id(id),
      translationx(translationx),
      translationy(translationy),
      rotation(rotation),
      scalex(scalex),
      scaley(scaley) {}

#endif
