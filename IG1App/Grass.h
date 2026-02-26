#ifndef H_Grass_H
#define H_Grass_H

#include "EntityWithTexture.h"
class Grass :
    public EntityWithTexture
{
public:
    Grass(GLdouble length, Texture* tex);
    void render(glm::mat4 const& modelViewMat) const override;
};

#endif H_Grass_H