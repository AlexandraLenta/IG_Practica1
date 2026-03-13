#include "BoxOutline.h"

BoxOutline::BoxOutline(GLdouble length, Texture* texOut, Texture* texIn) : EntityWithTexture(texOut), mTextureInside(texIn) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}

void
BoxOutline::render(glm::mat4 const& modelViewMat) const {
    if (mMesh != nullptr) {
        glm::mat4 aMat = modelViewMat * mModelMat;

        mShader->use();
        mShader->setUniform("modulate", mModulate);
        upload(aMat);

        if (mTexture != nullptr)
        {
            glEnable(GL_CULL_FACE);

            glCullFace(GL_FRONT);

            mTexture->bind();
            mMesh->render();
            mTexture->unbind();

            glCullFace(GL_BACK);

            mTextureInside->bind();
            mMesh->render();
            mTextureInside->unbind();

            glDisable(GL_CULL_FACE);
        }
    }
}