#include "Sphere.h"
#include "IndexMesh.h"

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians) {
    std::vector<glm::vec2> profile;
    profile.reserve(nParallels + 1);

    float theta = std::numbers::pi / 2;
    float increment = std::numbers::pi / nParallels;

    for (int i = 0; i <= nParallels; ++i) {
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        
        theta -= increment;
        
        profile.emplace_back(x, y);
    }

    mMesh = IndexMesh::generateByRevolution(profile, nMeridians);
}