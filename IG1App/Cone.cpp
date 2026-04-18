#include "Cone.h"
#include "IndexMesh.h"

Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples) {
    std::vector<glm::vec2> profile;

    profile.reserve(nRings + 1);

    // R: radio arriba
    // r: radio abajo

    // crear la figura
    for (int i = 0; i < nRings; ++i)
    {
    }

    mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}