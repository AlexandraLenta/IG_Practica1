#pragma once
#include "EntityWithTexture.h"
class Box :
    public EntityWithTexture
{
public:
    Box(GLdouble length, Texture* tex, Texture* texInside);
    void render(glm::mat4 const& modelViewMat) const override;

private:
    Mesh* mLidMesh;
    Texture* mTextureInside;
    GLdouble length;
};

