#include "EntityWithTexture.h"

EntityWithTexture::EntityWithTexture(Texture* tex, bool modulate) : EntityWithColors(),mTexture(tex), mModulate(modulate)
{
    mShader = Shader::get("texture");
}

void EntityWithTexture::render(glm::mat4 const& modelViewMat) const
{
    if (mMesh != nullptr) {
        glm::mat4 aMat = modelViewMat * mModelMat;

        mShader->use();
        mShader->setUniform("modulate", mModulate);
        upload(aMat);

        if (mTexture != nullptr)
        {
            mTexture->bind();
            mMesh->render();
            mTexture->unbind();
        }
    }
}