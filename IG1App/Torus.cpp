#include "Torus.h"
#include "IndexMesh.h"

Torus::Torus(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples): ColorMaterialEntity(glm::vec4(0, 1, 0, 1))
{
    // vector que almacena puntos en el plano xy
    std::vector<glm::vec2> profile;

    profile.reserve(nPoints + 1);

    // aumento del angulo en cada iteracion
    const float incAngle = glm::radians(360.0f) / nPoints;

    float theta = 0;

    // crear la figura
    for (int i = 0; i <= nPoints; ++i) 
    {
        float x = R + r * cos(theta); //R distancia delcentro del toro al centro del tubo
                                      //r *cos es desp dentro del cubo

        float y = r * sin(theta); // r * sin es altura del tubo
        profile.emplace_back(x, y);

        theta += incAngle;
    }

    mMesh = IndexMesh::generateByRevolution(profile, nSamples);

}
