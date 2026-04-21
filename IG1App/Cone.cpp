#include "Cone.h"
#include "IndexMesh.h"

Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples, glm::vec4 color) : ColorMaterialEntity(color) {
    std::vector<glm::vec2> profile;

    profile.reserve(nRings);

    // R: radio arriba
    // r: radio abajo
	
	// cambio en radio
	GLdouble radIncr = (r - R) / nRings;

	// la altura
	GLdouble heightIncr = h / nRings;

	GLdouble radius = r;
	GLdouble y = -h * 0.5;

	for (int i = 0; i <= nRings; i++)
	{
		profile.emplace_back(radius, y);

		radius -= radIncr;
		y += heightIncr;
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