#ifndef H_GlassParapet_H
#define H_GlassParapet_H

#include "EntityWithTexture.h"
class GlassParapet :
    public EntityWithTexture
{
public:
    explicit GlassParapet(GLdouble length, Texture* tex);
};

#endif H_GlassParapet_H