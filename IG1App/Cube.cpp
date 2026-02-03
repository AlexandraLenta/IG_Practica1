#include "Cube.h"

Cube::Cube(GLdouble length, glm::vec4 color): SingleColorEntity(color), mColor(color)
{
	mMesh = Mesh::generateCube(length);
}

Cube::~Cube() {

}

void Cube::render(const glm::mat4& modelViewMat) const
{
	if (mMesh == nullptr) return;

	glm::mat4 aMat = modelViewMat * mModelMat;

	mShader->use();
	mShader->setUniform("color", mColor);
	upload(aMat);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mMesh->render();

	glCullFace(GL_FRONT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	mMesh->render();

	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glDisable(GL_CULL_FACE);
}
