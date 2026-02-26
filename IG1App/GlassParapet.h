#ifndef H_GlassParapet_H
#define H_GlassParapet_H

#include "EntityWithTexture.h"
class GlassParapet :
    public EntityWithTexture
{
public:
    explicit GlassParapet(GLdouble x, GLdouble y, GLdouble z, Texture* tex);
    void render(glm::mat4 const& modelViewMat) const override;
};

#endif H_GlassParapet_H