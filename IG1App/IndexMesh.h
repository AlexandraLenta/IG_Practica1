#ifndef H_Mesh_H
#define H_Mesh_H

#include <numbers>
#include "Mesh.h"
class IndexMesh :
    public Mesh
{
protected :
    std::vector<GLuint> vIndexes;
    GLuint mIBO;

public:
    IndexMesh();
    void draw() const override;
    void load() override;
    void unload() override;

    static IndexMesh* generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples,
        GLfloat angleMax = 2 * std::numbers::pi);

};
#endif H_Mesh_H
