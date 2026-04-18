#include "Sphere.h"
#include "IndexMesh.h"

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians) {
    //// aumento del angulo en cada iteracion
    //const float incAngle = std::numbers::pi / nParallels;
    //float startAngle = std::numbers::pi / 2; // empezamos en pi/2 hasta -pi/2

    //// crear la figura
    //for (int i = 0; i <= nParallels; ++i)
    //{
    //    float angle = startAngle + i * incAngle;
    //    float x = radius * cos(angle); //R distancia delcentro del toro al centro del tubo
    //    //r *cos es desp dentro del cubo

    //    float y = radius * sin(angle); // r * sin es altura del tubo
    //    profile.emplace_back(x, y);
    //}

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