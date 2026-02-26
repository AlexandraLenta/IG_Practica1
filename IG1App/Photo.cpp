#include "Photo.h"

Photo::Photo(GLdouble length) : EntityWithTexture(), length(length) {
	mMesh = Mesh::generateRectangleTexCor(length, length, 1, 1);
	mTexture = new Texture();
	mTexture->loadColorBuffer(600, 600);
}

Photo::~Photo() {
	delete mTexture;
	mTexture = nullptr;
}

void
Photo::update() {
	mTexture->loadColorBuffer(600, 600);
}

GLuint* 
Photo::getImg() {
	GLuint pixels[32];
	glGetTexImage(GL_TEXTURE_2D, 0,
		GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, pixels);

	return pixels;
}