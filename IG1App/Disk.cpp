#include "Disk.h"
#include "IndexMesh.h"
Disk::Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples, glm::vec4 color) : ColorMaterialEntity(color) {

	std::vector<glm::vec2> profile;

	// r: radio interior
	// R: radio exterior

	profile.reserve(nRings + 1);
	GLdouble radius = r;
	// incrementa radio desde interior a exterior
	GLdouble dr = (R - r) / nRings;

	for (GLuint i = 0; i <= nRings; ++i)
	{
		profile.emplace_back(radius, 0.0);
		radius += dr;
	}

	mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}
