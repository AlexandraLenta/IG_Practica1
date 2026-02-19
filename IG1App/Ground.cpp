#include "Ground.h"

Ground :: Ground(GLdouble w, GLdouble h) : EntityWithTexture()
{
	mMesh = Mesh::generateRGBRectangle(w, h); // generar malla

	glm::mat4 model = glm::mat4(1.0f); // crear matriz identidad

	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotar el rectangulo horizontalmente
	setModelMat(model); 
}