#include "Box.h"

Box::Box(GLdouble length, Texture* tex, Texture* texInside) : EntityWithTexture(tex), mTextureInside(texInside), length(length) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);

    mLidMesh = Mesh::generateRectangleTexCor(length, length, 1, 1); // generar malla
    mLidMesh->load(); // cargar la nueva malla en el GPU
}

void
Box::render(glm::mat4 const& modelViewMat) const {
    if (mMesh != nullptr) {
        glm::mat4 aMat = modelViewMat * mModelMat;

        mShader->use();
        mShader->setUniform("modulate", mModulate);
        upload(aMat);

        if (mTexture != nullptr)
        {
            glEnable(GL_CULL_FACE);

            glCullFace(GL_BACK);

            mTexture->bind();
            mMesh->render();
            mTexture->unbind();

            glCullFace(GL_FRONT);

            mTextureInside->bind();
            mMesh->render();
            mTextureInside->unbind();

            glCullFace(GL_BACK);

            glm::mat4 mat2 = glm::translate(mat2, glm::vec3(0, length, 0));
            mat2 = glm::rotate(mModelMat, glm::radians(90.0f), glm::vec3(1, 0, 0));

            upload(modelViewMat * mat2);

            mTexture->bind();
            mLidMesh->render();
            mTexture->unbind();

            glCullFace(GL_FRONT);

            mTextureInside->bind();
            mLidMesh->render();
            mTextureInside->unbind();

            glDisable(GL_CULL_FACE);
        }
    }
}