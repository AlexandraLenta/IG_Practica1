#include "Cone.h"
#include "IndexMesh.h"

Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples) {
    std::vector<glm::vec2> profile;

    profile.reserve(nRings + 1);

    // R: radio arriba
    // r: radio abajo
    // 
    // cambio en radio
    GLdouble dr = (R - r) / nRings;
    // la altura
    GLdouble dy= h/nRings;


    // 
    GLdouble y = h * 0.5;
    GLdouble radius = r;

    // crear la figura
    for (int i = 0; i <= nRings; ++i)
    {
        profile.emplace_back(radius, y);
        radius += dr;
        y -= dy;
    }

    mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}

//#include "Cone.h"
//#include "IndexMesh.h"
//
//Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples) {
//    // R: radio arriba
//    // r: radio abajo
//
//    std::vector<glm::vec2> profile;
//    profile.reserve(nRings + 1);
//
//    GLdouble dy = h / nRings;
//
//    // empezamos abajo
//    GLdouble y = -h * 0.5;
//
//    for (int i = 0; i <= nRings; ++i)
//    {
//        // interpolacion?
//        GLdouble t = (y + h * 0.5) / h;
//        GLdouble radius = r + t * (R - r);
//
//        profile.emplace_back(radius, y);
//
//        y += dy;
//    }
//
//    mMesh = IndexMesh::generateByRevolution(profile, nSamples);
//}