#include "Box.h"

Box::Box(GLdouble length, Texture* tex, Texture* texInside) : EntityWithTexture(tex), length(length), mTextureInside(texInside) {
    mMesh = Mesh::generateBoxOutlineTexCor(length);

    mMeshTop = Mesh::generateRectangleTexCor(length, length, 1, 1); // generar malla
    mMeshTop->load(); // cargar la nueva malla en el GPU
}

Box::~Box() {
    delete mMeshTop;
}

void
Box::render(glm::mat4 const& modelViewMat) const {
    if (mMesh != nullptr && mMeshTop != nullptr) {
        glm::mat4 aMat = modelViewMat * mModelMat;

        // matriz para el fondo
        glm::mat4 matBottom = glm::mat4(1.0f);
        matBottom = glm::translate(glm::mat4(1.0f), glm::vec3(0, -length / 2, 0)); //mover hacia abajo
        matBottom = glm::rotate(matBottom, glm::radians(-90.0f), glm::vec3(1, 0, 0)); // rotar con el interior arriba

        glm::mat4 matTop = glm::mat4(1.0f); // matriz para la tapa
        matTop = glm::translate(matTop, glm::vec3(-length / 2, length / 2, 0)); // mover hacia el centro
        matTop = glm::rotate(matTop, glm::radians(topAngle), glm::vec3(0, 0, 1)); // rotar el angulo necesario
        matTop = glm::rotate(matTop, glm::radians(90.0f), glm::vec3(1, 0, 0)); // rotar para que este horizontal
        matTop = glm::translate(matTop, glm::vec3(length / 2, 0, 0)); // mover hacia su posicion como tapa

        glm::mat4 aMatBottom = modelViewMat * mModelMat * matBottom;
        glm::mat4 aMatTop = modelViewMat * mModelMat * matTop;

        mShader->use();
        mShader->setUniform("modulate", mModulate);

        if (mTexture != nullptr) {
            

            glEnable(GL_CULL_FACE);

            //exterior
            glCullFace(GL_FRONT);
            mTexture->bind();
            upload(aMat);
            mMesh->render();

            upload(aMatBottom); // renderizar respecto a la matriz de la caja
            mMeshTop->render();
            upload(aMatTop); // renderizar respecto a la matriz de la caja
            mMeshTop->render();
            mTexture->unbind();

            //interior
            glCullFace(GL_BACK);
            mTextureInside->bind();
            upload(aMat);
            mMesh->render();

            upload(aMatBottom); // renderizar respecto a la matriz de la caja
            mMeshTop->render();
            upload(aMatTop); // renderizar respecto a la matriz de la caja
            mMeshTop->render();
            mTextureInside->unbind();

            glDisable(GL_CULL_FACE);
        }
    }
}

void
Box::update() {
    if (topAngle >= 180.0f)
        moveDir = -1;

    else if (topAngle <= 0.0f)
        moveDir = 1;

    topAngle += 1.0f * moveDir;
}
