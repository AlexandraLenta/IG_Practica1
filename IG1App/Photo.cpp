#include "Photo.h"

Photo::Photo(GLdouble length) : EntityWithTexture(), length(length) {
	mMesh = Mesh::generateRectangleTexCor(length, length, 1, 1);
	mTexture = new Texture();
}

Photo::~Photo() {
	delete mTexture;
	mTexture = nullptr;
}

void
Photo::update() {
	mTexture->loadColorBuffer(600, 600);
}