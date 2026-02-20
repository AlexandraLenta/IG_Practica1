#pragma once
#include "SingleColorEntity.h"
class Star3D :
    public SingleColorEntity
{
public:
    Star3D(GLdouble radius, GLuint pointNr, GLdouble coorZ);
    void render(const glm::mat4& modelViewMat) const override;
};

