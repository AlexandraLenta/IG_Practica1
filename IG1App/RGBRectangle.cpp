#include "RGBRectangle.h"

RGBRectangle::RGBRectangle(GLdouble w, GLdouble h) : EntityWithColors() {
	// crea una malla triangular
	mMesh = Mesh::generateRGBRectangle(w, h);
}

void RGBRectangle::render(glm::mat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);

		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();

		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		glFrontFace(GL_CCW);
		glDisable(GL_CULL_FACE);
	}
}