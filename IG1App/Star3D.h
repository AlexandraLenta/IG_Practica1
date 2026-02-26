#ifndef H_Star3D_H
#define H_Star3D_H

#include "EntityWithTexture.h"

class Star3D :
    public EntityWithTexture
{
public:
    Star3D(GLdouble radius, GLuint pointNr, GLdouble coorZ, Texture* tex);
    void transformModelMat(glm::mat4 newMat);
    void render(const glm::mat4& modelViewMat) const override;
    void update() override;

private:
    float angle = 0.0f;
    glm::mat4 mPositionMat;

    void rotate(float angle);
};

#endif H_Star3D_H