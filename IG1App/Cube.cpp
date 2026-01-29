#include "Cube.h"
#include "Mesh.h"

Cube::Cube(GLdouble length, glm::vec4 color): SingleColorEntity(color)
{
	mMesh = Mesh::generateCube(length);
}

void Cube::render(const glm::mat4& modelViewMat) const
{
	if (mMesh == nullptr) return;

	glm::mat4 aMat = modelViewMat * mModelMat;

	mShader->use();
	mShader->setUniform("color", mColor);
	upload(aMat);

	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_POINT);

	mMesh->render();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
