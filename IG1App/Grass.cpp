#include "Grass.h"

Grass::Grass(GLdouble length, Texture* tex) : EntityWithTexture(tex) {
	mShader = Shader::get("texture:texture_alpha");
	mMesh = Mesh::generateRectangleTexCor(length, length, 1, 1);
}

void
Grass::render(glm::mat4 const& modelViewMat) const {
    if (mMesh != nullptr) {
        glm::mat4 aMat = modelViewMat * mModelMat;

        mShader->use();
        mShader->setUniform("modulate", mModulate);
        upload(aMat);

        if (mTexture != nullptr)
        {
            mTexture->bind();
            mMesh->render();

            upload(modelViewMat * glm::rotate(mModelMat, glm::radians(120.0f), glm::vec3(0, 1, 0))); // rotar 360/3 grados respecto a la primera matriz

            mMesh->render();

            upload(modelViewMat * glm::rotate(mModelMat, glm::radians(240.0f), glm::vec3(0, 1, 0))); // rotar 2*360/3 grados respecto a la primera matriz

            mMesh->render();

            mTexture->unbind();
        }
    }
}