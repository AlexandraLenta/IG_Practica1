#include "Ground.h"

Ground :: Ground(GLdouble w, GLdouble h) : EntityWithColors()
{
	mMesh = Mesh::generateRGBRectangle(w, h);
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::rotate(model,glm::radians(-90.0f),glm::vec3(1.0f, 0.0f, 0.0f));
	setModelMat(model);
}

void Ground:: render(glm::mat4 const& modelViewMat) const 
{




}