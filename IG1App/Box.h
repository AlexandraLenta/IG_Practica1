#pragma once
#include "EntityWithTexture.h"
class Box :
    public EntityWithTexture
{
public:
    Box(GLdouble length, Texture* tex, Texture* texInside);
    void render(glm::mat4 const& modelViewMat) const override;
    void update() override;

private:
    Mesh* mMeshTop;
    Texture* mTextureInside;
    glm::mat4 mModelMatTop;
    glm::mat4 mModelMatBottom;
    GLdouble length;
    float topAngle = 0.0f;
    int moveDir = 1;

    void renderSides() const;
    void renderBottom() const;
    void renderTop() const;

    void moveLid();
};

