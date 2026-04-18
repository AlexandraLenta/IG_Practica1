#include "Sphere.h"
#include "IndexMesh.h"

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians) {
    std::vector<glm::vec2> profile;
    profile.reserve(nParallels + 1);

    float theta = std::numbers::pi / nParallels;

    for (int i = 0; i <= nParallels; ++i) {
        float x = radius * sin(theta * i);
        float y = radius * cos(theta * i);

        profile.emplace_back(x, y);
    }

    mMesh = IndexMesh::generateByRevolution(profile, nMeridians);
}