#include "ColorMaterialEntity.h"

ColorMaterialEntity::ColorMaterialEntity(glm::vec4 color) : EntityWithMaterial() {
	/*mShader = Shader::get("simple_light");
	mNormalsShader = Shader::get("normals");*/

    mMaterial.setAmb(color);
    mMaterial.setDiff(color);
    mMaterial.setSpec(color);
}

void
ColorMaterialEntity::render(const glm::mat4& modelViewMat) const {
    EntityWithMaterial::render(modelViewMat);
    if (!mShowNormals || mMesh == nullptr) return;

    glm::mat4 aMat = modelViewMat * mModelMat;

    Shader* normalsSh = Shader::get("normals");
    normalsSh->use();
    normalsSh->setUniform("modelView", aMat);

    mMesh->render();
}

void
ColorMaterialEntity::toggleShowNormals() {
	mShowNormals = !mShowNormals;
}

bool ColorMaterialEntity::mShowNormals = false;