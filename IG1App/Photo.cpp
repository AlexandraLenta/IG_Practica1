#include "Photo.h"

Photo::Photo(GLdouble length) : EntityWithTexture(), length(length) {
	mMesh = Mesh::generateRectangleTexCor(length, length, 1, 1);
	mTexture->loadColorBuffer(length, length);
}

void
Photo::update() {
	mTexture->loadColorBuffer(length, length);
}