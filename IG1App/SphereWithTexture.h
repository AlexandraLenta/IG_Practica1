#ifndef H_Sphere_H
#define H_Sphere_H
#include "EntityWithTexture.h"

class SphereWithTexture :
    public EntityWithTexture
{
public:
    SphereWithTexture(GLfloat radius, GLuint nParallels, GLuint nMeridians, Texture* tex);
};

#endif H_Sphere_H