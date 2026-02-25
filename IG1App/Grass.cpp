#include "Grass.h"

Grass::Grass(GLdouble length, Texture* tex) : EntityWithTexture(tex) {
	mShader = Shader::get("texture:texture_alpha");
	mMesh = Mesh::generateRectangleTexCor(length, length, 1, 1);

    mModelMat2 = glm::rotate(mModelMat, glm::radians(120.0f), glm::vec3(0, 1, 0)); // segunda matriz grass, girada 360/3 grados respecto a la primera
    mModelMat3 = glm::rotate(mModelMat, glm::radians(240.0f), glm::vec3(0, 1, 0)); // tercera matriz grass, girada 2*360/3 grados respecto a la primera
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

            upload(modelViewMat * mModelMat2);

            mMesh->render();

            upload(modelViewMat * mModelMat3);

            mMesh->render();

            mTexture->unbind();
        }
    }
}