#include "EntityWithMaterial.h"

EntityWithMaterial::EntityWithMaterial() {
	mShader = Shader::get("light");
}

void EntityWithMaterial::render(const glm::mat4& modelViewMat) const
{
	if (mMesh == nullptr) return;

	mShader->use();
	mMaterial.upload(*mShader);
	glm::mat4 mvMat = modelViewMat * mModelMat;

	upload(mvMat);
	mMesh->render();
}
