#include "RGBTriangle.h"

RGBTriangle::RGBTriangle(GLdouble r) : EntityWithColors() {
	// crea una malla triangular
	mMesh = Mesh::generateRGBRectangle(r);
}