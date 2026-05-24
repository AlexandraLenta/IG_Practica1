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

	if (mShowNormals) {
		Shader* normalsSh = Shader::get("normals");
		normalsSh->use();
		normalsSh->setUniform("modelView", aMat);
		mMesh->render();
	}
}

void
EntityWithMaterial::toggleShowNormals() {
	mShowNormals = !mShowNormals;
}

bool EntityWithMaterial::mShowNormals = false;