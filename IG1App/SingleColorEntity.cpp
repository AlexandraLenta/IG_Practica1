#include "SingleColorEntity.h"


SingleColorEntity::SingleColorEntity(glm::vec4 color = {1.0, 1.0, 1.0, 1.0}) {
	mColor = color;
	mShader = Shader::get("simple");
}

glm::vec4 SingleColorEntity::getColor() const {

}

void SingleColorEntity::setColor(glm::vec4) {

}

void SingleColorEntity::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("color", mColor);
		upload(aMat);
		mMesh->render();
	}
}