#include "Star3D.h"

Star3D::Star3D(GLdouble radius, GLuint pointNr, GLdouble coorZ, Texture* tex) : EntityWithTexture(tex) {
	mMesh = Mesh::generateStar3DTexCor(radius, pointNr, coorZ);
}

void 
Star3D::render(const glm::mat4& modelViewMat) const {
	// dibujar primera estrella
	EntityWithTexture::render(modelViewMat);
	
	// dibujar segunda estrella
	glm::mat4 aMatFlip = modelViewMat * glm::rotate(mModelMat, glm::radians(180.0f), { 0, 1, 0 });;
	upload(aMatFlip);

	mTexture->bind();
	mMesh->render();
	mTexture->unbind();
}

void
Star3D::update() {
	rotate(1);
}

void 
Star3D::rotate(float a) {
	//increase angle
	angle += a;

	//rotacion en y
	glm::mat4 rotationYMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));
	//rotacion en z
	glm::mat4 rotationZMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1));

	setModelMat(rotationYMat * rotationZMat * mModelMat);
}