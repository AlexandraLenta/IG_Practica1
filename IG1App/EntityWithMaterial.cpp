#include "EntityWithMaterial.h"

EntityWithMaterial::EntityWithMaterial() {
	mShader = Shader::get("light");
}

void EntityWithMaterial::render(const glm::mat4& modelViewMat) const
{
	if (mMesh == nullptr) return;

	mShader->use();
	mMaterial.upload(*mShader);
	glm::mat4 aMat = modelViewMat * mModelMat;

	upload(aMat);
	mMesh->render();
}
