#include "RGBRectangle.h"

RGBRectangle::RGBRectangle(GLdouble w, GLdouble h) : EntityWithColors() {
	// crea una malla triangular
	mMesh = Mesh::generateRGBRectangle(w, h);
}