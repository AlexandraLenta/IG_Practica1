#ifndef H_Box_H
#define H_Box_H

#include "BoxOutline.h"

class Box :
    public BoxOutline
{
public:
    Box(GLdouble length, Texture* tex, Texture* texInside);
    ~Box();
    void render(glm::mat4 const& modelViewMat) const override;
    void update() override;

private:
    Mesh* mMeshTop;
    glm::mat4 mModelMatTop;
    glm::mat4 mModelMatBottom;
    GLdouble length;
    float topAngle = 0.0f;
    int moveDir = 1;

    void renderMesh(Mesh* mesh) const;
};

#endif H_Box_H