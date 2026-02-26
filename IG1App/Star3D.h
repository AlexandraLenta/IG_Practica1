#ifndef H_Star3D_H
#define H_Star3D_H

#include "EntityWithTexture.h"

class Star3D :
    public EntityWithTexture
{
public:
    Star3D(GLdouble radius, GLuint pointNr, GLdouble coorZ, Texture* tex);
    void render(const glm::mat4& modelViewMat) const override;
    void update() override;

private:
    float angle = 0.0f;

    void rotate(float angle);
};

#endif H_Star3D_H