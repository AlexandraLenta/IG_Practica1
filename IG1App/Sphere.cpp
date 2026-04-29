#include "Sphere.h"
#include "IndexMesh.h"

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians, glm::vec3 color) : ColorMaterialEntity(color) {
    mMesh = IndexMesh::generateSphere(radius, nParallels, nMeridians);
}