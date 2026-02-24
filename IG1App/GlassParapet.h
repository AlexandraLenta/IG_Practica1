#pragma once
#include "EntityWithTexture.h"
class GlassParapet :
    public EntityWithTexture
{
public:
    explicit GlassParapet(GLdouble lenght, Texture* tex);
    void render(glm::mat4 const& modelViewMat) const override;
};

