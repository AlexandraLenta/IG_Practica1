#ifndef H_Droid_H
#define H_Droid_H
#include "CompoundEntity.h"

class Texture;

class Droid :
    public CompoundEntity
{
public:
    Droid(GLdouble radius, Texture* bodyTex);
};

#endif H_Droid_H