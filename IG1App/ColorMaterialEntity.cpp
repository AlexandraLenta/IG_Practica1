#include "ColorMaterialEntity.h"

ColorMaterialEntity::ColorMaterialEntity(glm::vec4 color) : SingleColorEntity(color) {
	mShader = Shader::get("simple_light");
	mNormalsShader = Shader::get("normals");
}

void
ColorMaterialEntity::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("color", mColor);
		upload(aMat);

		mMesh->render();

		if (ColorMaterialEntity::mShowNormals) {
			mNormalsShader->use();
			mMesh->render();
		}
	}
}

void
ColorMaterialEntity::toggleShowNormals() {
	mShowNormals = !mShowNormals;
}

bool ColorMaterialEntity::mShowNormals = false;