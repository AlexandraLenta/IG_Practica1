#pragma once
#include "EntityWithTexture.h"
class Grass :
    public EntityWithTexture
{
public:
    Grass(GLdouble length, Texture* tex);
    void render(glm::mat4 const& modelViewMat) const override;
private:
    glm::mat4 mModelMat2;
    glm::mat4 mModelMat3;
};

