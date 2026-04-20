#pragma once
#include "EntityWithTexture.h"

class SphereWithTexture :
    public EntityWithTexture
{
public:
    SphereWithTexture(GLfloat radius, GLuint nParallels, GLuint nMeridians, Texture* tex);
};

