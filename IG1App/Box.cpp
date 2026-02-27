#include "Box.h"

Box::Box(GLdouble length, Texture* tex, Texture* texInside) : EntityWithTexture(tex), mTextureInside(texInside), length(length), mModelMatTop(1.0f) {
	mMesh = Mesh::generateBoxOutlineTexCor(length, length, length);

    mMeshTop = Mesh::generateRectangleTexCor(length, length, 1, 1); // generar malla
    mMeshTop->load(); // cargar la nueva malla en el GPU
}

Box::~Box() {
    delete mMeshTop;
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

            renderMesh(mMesh); // renderizar lados

            if (mMeshTop) // si existe
            {
                // mover matriz para el fondo
                glm::mat4 matBottom = glm::mat4(1.0f);
                matBottom = glm::translate(glm::mat4(1.0f), glm::vec3(0, -length / 2, 0)); // mover hacia abajo
                matBottom = glm::rotate(matBottom, glm::radians(-90.0f), glm::vec3(1, 0, 0)); // rotar con el interior arriba

                upload(modelViewMat * mModelMat * matBottom); // renderizar respecto a la matriz de la caja

                renderMesh(mMeshTop); // renderizar fondo

                glm::mat4 matTop = glm::mat4(1.0f); // resetear matriz

                matTop = glm::translate(matTop, glm::vec3(-length / 2, length / 2, 0)); // mover hacia el centro

                matTop = glm::rotate(matTop, glm::radians(topAngle), glm::vec3(0, 0, 1)); // rotar el angulo necesario

                matTop = glm::rotate(matTop, glm::radians(90.0f), glm::vec3(1, 0, 0)); // rotar para que este horizontal

                matTop = glm::translate(matTop, glm::vec3(length / 2, 0, 0)); // mover hacia su posicion como tapa

                upload(modelViewMat * mModelMat * matTop); // renderizar respecto a la matriz de la caja

                renderMesh(mMeshTop); // renderizar tapa
            }

            glDisable(GL_CULL_FACE);
        }
    }
}

void
Box::renderMesh(Mesh* mesh) const {
    glCullFace(GL_FRONT);

    mTexture->bind();
    mesh->render();
    mTexture->unbind();

    glCullFace(GL_BACK);

    mTextureInside->bind();
    mesh->render();
    mTextureInside->unbind();
}

void
Box::update() {
    if (topAngle >= 180.0f)
        moveDir = -1;

    else if (topAngle <= 0.0f)
        moveDir = 1;

    topAngle += 1.0f * moveDir;
}
