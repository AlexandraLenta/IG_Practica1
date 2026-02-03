#include "SingleColorEntity.h"


SingleColorEntity::SingleColorEntity(glm::vec4 color = {1.0, 1.0, 1.0, 1.0}) : Abs_Entity() {
	mColor = color;
	mShader = Shader::get("simple");
}

SingleColorEntity::~SingleColorEntity() {

}

glm::vec4 SingleColorEntity::getColor() const {
	return mColor;
}

void SingleColorEntity::setColor(glm::vec4 color) {
	mColor = color;
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