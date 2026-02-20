#include "Star3D.h"

Star3D::Star3D(GLdouble radius, GLuint pointNr, GLdouble coorZ, Texture* tex) : EntityWithTexture(tex) {
	mMesh = Mesh::generateStar3D(radius, pointNr, coorZ);
}

void 
Star3D::render(const glm::mat4& modelViewMat) const {
	// dibujar primera estrella
	EntityWithTexture::render(modelViewMat);

	// duplicar la estrella
	glm::mat4 modelMatFlip = mModelMat;
	
	// rotar la estrella
	modelMatFlip = glm::rotate(modelMatFlip, glm::radians(180.0f), { 0, 1, 0 });
	
	// dibujar segunda estrella
	glm::mat4 aMatFlip = modelViewMat * modelMatFlip;
	upload(aMatFlip);

	mTexture->bind();
	mMesh->render();
	mTexture->unbind();
}

void
Star3D::update() {

}