#include "ColorMaterialEntity.h"

ColorMaterialEntity::ColorMaterialEntity(glm::vec4 color) : SingleColorEntity(color) {
	mShader = Shader::get("simple_light");
}

void
ColorMaterialEntity::render(const glm::mat4& modelViewMat) const {
	SingleColorEntity::render(modelViewMat);

	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("normals", {1.0, 1.0, 0.0, 1.0});
		upload(aMat);

		mMesh->render();
	}
}