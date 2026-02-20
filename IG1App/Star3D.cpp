#include "Star3D.h"

Star3D::Star3D(GLdouble radius, GLuint pointNr, GLdouble coorZ) : SingleColorEntity({ 0,0,0,1 }) {
	mMesh = Mesh::generateStar3D(radius, pointNr, coorZ);
}

void 
Star3D::render(const glm::mat4& modelViewMat) const {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	SingleColorEntity::render(modelViewMat);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}