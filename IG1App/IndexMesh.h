#ifndef H_IndexMesh_H
#define H_IndexMesh_H

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

    void buildNormalVectors();

    static IndexMesh* generateIndexedBox8(GLdouble l);
    static IndexMesh* generateIndexedBox(GLdouble l);

};
#endif H_IndexMesh_H