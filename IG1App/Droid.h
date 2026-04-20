#pragma once
#include "CompoundEntity.h"

class Texture;

class Droid :
    public CompoundEntity
{
public:
    Droid(GLdouble radius, Texture* bodyTex);
};

