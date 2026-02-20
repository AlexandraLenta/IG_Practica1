#include "BoxOutline.h"

BoxOutline::BoxOutline(GLdouble length) : SingleColorEntity({0.0, 0.0, 0.0, 1.0}) {
	mMesh = Mesh::generateBoxOutline(length);
}

void
BoxOutline::render(const glm::mat4& modelViewMat) const {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	SingleColorEntity::render(modelViewMat);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}