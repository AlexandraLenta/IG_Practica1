#pragma once
#include "EntityWithTexture.h"
class GlassParapet :
    public EntityWithTexture
{
public:
    explicit GlassParapet(GLdouble length, Texture* tex);
    void render(glm::mat4 const& modelViewMat) const override;
};

