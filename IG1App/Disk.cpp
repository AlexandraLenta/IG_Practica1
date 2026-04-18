#include "Disk.h"
#include "IndexMesh.h"
Disk::Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples) {

	std::vector<glm::vec2> profile;

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
