#include "RGBCube.h"

RGBCube::RGBCube(GLdouble length) {
	mMesh = Mesh::generateRGBCubeTriangles(length);
}

void
RGBCube::update() {

}