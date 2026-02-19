#include "EntityWithTexture.h"

EntityWithTexture::EntityWithTexture() : EntityWithColors(),mTexture(nullptr), mModulate(false)
{
    mShader = Shader::get("texture");
}

void EntityWithTexture::render(glm::mat4 const& modelViewMat) const
{
    glm::mat4 aMat = modelViewMat * mModelMat;

    mShader->use();
    upload(aMat);

    mShader->setUniform("modulate", mModulate);

    if (mTexture != nullptr)
    {
        mTexture->bind();
        mMesh->render();
        mTexture->unbind();
    }
}