#include "Torus.h"
#include "IndexMesh.h"

Torus::Torus(GLdouble R, GLdouble r, GLuint nPoints = 40, GLuint nSamples = 40): SingleColorEntity(glm::vec4(0, 1, 0, 1))
{
    // vector que almacena puntos en el plano xy
    std::vector<glm::vec2> profile;

    profile.reserve(nPoints + 1);

    //aumento del angulo en cada ite
    const float incAngle =glm::radians(360) / nPoints;

    for (int i = 0; i <= nPoints; ++i) 
    {
        float angle = i * incAngle;
        float x = R + r * cos(angle); //R distancia delcentro del toro al centro del tubo
                                      //r *cos es desp dentro del cubo

        float y = r * sin(angle); // r * sin es altura del tubo
        profile.emplace_back(x, y);
    }

    mMesh = IndexMesh::generateByRevolution(profile, nSamples);

}
