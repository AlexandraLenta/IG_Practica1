#include "RGBCube.h"

RGBCube::RGBCube(GLdouble length) : EntityWithColors(), length(length), angle(0), axis(1.0, 0.0, 0.0), position( length / 2, length / 2, -length / 2) {
	mMesh = Mesh::generateRGBCubeTriangles(length);
}

void
RGBCube::update() {
	angle += 1.0f;
	if (angle >= 180.0f) {
		angle = 0.0f;
		// x-> z -> y
		if (axis.x > 0.0f) { // if moving in x, change to z
			axis = { 0.0, 0.0, 1.0 };
			position = { length / 2, -length/2, length/2};
		}
		else if (axis.y > 0.0f) { // if moving in y, change to x
			axis = { 1.0, 0.0, 0.0 };
			position = { length / 2, length / 2, -length / 2 };
		}
		else if (axis.z > 0.0f) { // if moving in z, change to y
			axis = { 0.0, 1.0, 0.0 };
			position = { -length / 2, length / 2, length / 2 };
		}
	}
	rotate(angle);
}

void 
RGBCube::rotate(GLfloat angle) {
	mModelMat = glm::mat4(1.0f);

	mModelMat = glm::rotate(mModelMat, (float)glm::radians(angle), axis);
	mModelMat = glm::translate(mModelMat, position);
}