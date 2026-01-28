#include "RGBTriangle.h"

RGBTriangle::RGBTriangle(GLdouble r, GLdouble posX, GLdouble posY, GLdouble posZ) : EntityWithColors(), position(posX, posY, posZ), originalDisplacement(posX, posY, posZ), radius(r) {
	// crea una malla triangular
	mMesh = Mesh::generateRGBTriangle(r, posX, posY);
}

void
RGBTriangle::update() {
	rotate(2);
}

void
RGBTriangle::rotate(GLdouble d) {
	angle += d;

	position.x = radius * glm::cos(glm::radians(angle));
	position.y = radius * glm::sin(glm::radians(angle));

	mModelMat = glm::translate(mModelMat, position);
	mModelMat = glm::rotate(mModelMat, (float)glm::radians(d), glm::vec3(0.0, 0.0, 1.0));
	mModelMat = glm::translate(mModelMat, -position);
}