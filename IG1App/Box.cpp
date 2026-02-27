#include "Box.h"

Box::Box(GLdouble length, Texture* tex, Texture* texInside) : EntityWithTexture(tex), mTextureInside(texInside), length(length), mModelMatTop(1.0f) {
	mMesh = Mesh::generateBoxOutlineTexCor(length, length, length);

    mMeshTop = Mesh::generateRectangleTexCor(length, length, 1, 1); // generar malla
    mMeshTop->load(); // cargar la nueva malla en el GPU

    // mover matriz para la tapa
    mModelMatTop = glm::translate(glm::mat4(1.0f), glm::vec3(0, length / 2, 0)); // mover hacia arriba
    mModelMatTop = glm::rotate(mModelMatTop, glm::radians(90.0f), glm::vec3(1, 0, 0)); // rotar con el interior abajo

    // mover matriz para el fondo
    mModelMatBottom = glm::translate(glm::mat4(1.0f), glm::vec3(0, -length / 2, 0)); // mover hacia abajo
    mModelMatBottom = glm::rotate(mModelMatBottom, glm::radians(-90.0f), glm::vec3(1, 0, 0)); // rotar con el interior arriba
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
                upload(modelViewMat * mModelMat * mModelMatBottom);

                renderLid(); // renderizar fondo

                upload(modelViewMat * mModelMat * mModelMatTop);

                renderLid(); // renderizar tapa
            }

            glDisable(GL_CULL_FACE);
        }
    }
}

void
Box::renderSides() const {
    glCullFace(GL_FRONT);

    mTexture->bind();
    mMesh->render();
    mTexture->unbind();

    glCullFace(GL_BACK);

    mTextureInside->bind();
    mMesh->render();
    mTextureInside->unbind();
}

void
Box::renderLid() const {
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