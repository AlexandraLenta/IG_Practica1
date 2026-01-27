#include "RGBTriangle.h"

RGBTriangle::RGBTriangle(GLdouble r, GLdouble posX, GLdouble posY) : EntityWithColors() {
	// crea una malla triangular
	mMesh = Mesh::generateRGBTriangle(r, posX, posY);
}