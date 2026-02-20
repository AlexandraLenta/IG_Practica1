#pragma once
#include "EntityWithTexture.h"

class Star3D :
    public EntityWithTexture
{
public:
    Star3D(GLdouble radius, GLuint pointNr, GLdouble coorZ, Texture* tex);
    void render(const glm::mat4& modelViewMat) const override;
    void update() override;
};

