#include "Sphere.h"
#include "IndexMesh.h"

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians) {
    mMesh = IndexMesh::generateSphere(radius, nParallels, nMeridians);
}