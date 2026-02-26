#include "Photo.h"
#include "IG1App.h"

Photo::Photo(GLdouble length) : EntityWithTexture(), length(length) {
	mMesh = Mesh::generateRectangleTexCor(length, length, 1, 1);
	mTexture = new Texture();
	mTexture->loadColorBuffer(IG1App::s_ig1app.viewPort().width(), IG1App::s_ig1app.viewPort().height());
}

Photo::~Photo() {
	delete mTexture;
	mTexture = nullptr;
}

void
Photo::update() {
	mTexture->loadColorBuffer(IG1App::s_ig1app.viewPort().width(), IG1App::s_ig1app.viewPort().height());
}

GLuint* 
Photo::getImg() {
	GLuint pixels[32];
	glGetTexImage(GL_TEXTURE_2D, 0,
		GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, pixels);

	return pixels;
}