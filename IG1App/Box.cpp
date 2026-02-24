#include "Box.h"

Box::Box(GLdouble length, Texture* tex, Texture* texInside) : EntityWithTexture(tex), mTextureInside(texInside), length(length), mModelMatTop(1.0f) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);

    mMeshTop = Mesh::generateRectangleTexCor(length, length, 1, 1); // generar malla
    mMeshTop->load(); // cargar la nueva malla en el GPU

    mModelMatTop = glm::translate(glm::mat4(1.0f), glm::vec3(0, length / 2, 0));
    mModelMatTop = glm::rotate(mModelMatTop, glm::radians(90.0f), glm::vec3(1, 0, 0));
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

            renderSides(); // renderizar lados

            if (mMeshTop) // si existe
            {
                glm::mat4 mModelMatBottom = glm::translate(glm::mat4(1.0f), glm::vec3(0, -length / 2, 0)); // mover hacia abajo
                mModelMatBottom = glm::rotate(mModelMatBottom, glm::radians(-90.0f), glm::vec3(1, 0, 0)); // rotar 90 grados, con el interior hacia arriba

                upload(modelViewMat * mModelMatBottom);

                renderBottom(); // renderizar fondo

                upload(modelViewMat * mModelMatTop);

                renderTop(); // renderizar tapa
            }

            glDisable(GL_CULL_FACE);
        }
    }
}

void
Box::renderSides() const {
    glCullFace(GL_BACK);

    mTexture->bind();
    mMesh->render();
    mTexture->unbind();

    glCullFace(GL_FRONT);

    mTextureInside->bind();
    mMesh->render();
    mTextureInside->unbind();
}

void
Box::renderBottom() const {
    glCullFace(GL_BACK);

    mTexture->bind();
    mMeshTop->render();
    mTexture->unbind();

    glCullFace(GL_FRONT);

    mTextureInside->bind();
    mMeshTop->render();
    mTextureInside->unbind();
}

void 
Box::renderTop() const {
    glCullFace(GL_BACK);

    mTexture->bind();
    mMeshTop->render();
    mTexture->unbind();

    glCullFace(GL_FRONT);

    mTextureInside->bind();
    mMeshTop->render();
    mTextureInside->unbind();
}

void
Box::update() {
    if (topAngle >= 180.0f)
        moveDir = -1;

    else if (topAngle <= 0.0f)
        moveDir = 1;

    topAngle += 1.0f * moveDir;

    moveLid();
}

void
Box::moveLid() {
    mModelMatTop = glm::mat4(1.0f); // resetear matriz

    mModelMatTop = glm::translate(mModelMatTop, glm::vec3(-length/2, length / 2, 0));

    mModelMatTop = glm::rotate(mModelMatTop, glm::radians(topAngle), glm::vec3(0, 0, 1));

    mModelMatTop = glm::rotate(mModelMatTop, glm::radians(90.0f), glm::vec3(1, 0, 0));

    mModelMatTop = glm::translate(mModelMatTop, glm::vec3(length/2, 0, 0));

}