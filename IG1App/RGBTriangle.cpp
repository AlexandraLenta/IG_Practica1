#include "RGBTriangle.h"

RGBTriangle::RGBTriangle(GLdouble r, GLdouble pos) : EntityWithColors(), position(pos) {
	// crea una malla triangular
	mMesh = Mesh::generateRGBTriangle(r);
}

void
RGBTriangle::update() {
	rotate(90, 2);
}

void
RGBTriangle::rotate(GLdouble l, GLdouble g) {
	localAngle += l;
	globalAngle += g;

	glm::mat4 localRotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(localAngle), glm::vec3(0.0, 0.0, 1.0));

	glm::mat4 globalRotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(globalAngle), glm::vec3(0.0, 0.0, 1.0));

	glm::mat4 globalRotationFinal = glm::translate(globalRotationMat, glm::vec3(position, 0.0, 0.0));

	this->setModelMat(globalRotationFinal * localRotationMat);
}