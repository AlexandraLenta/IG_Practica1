#include "Ground.h"

Ground::Ground(GLdouble w, GLdouble h, Texture* tex) : EntityWithTexture(tex, false)
{
	mMesh = Mesh::generateRectangleTexCor(w, h, 4, 4); // generar malla

	glm::mat4 model = glm::mat4(1.0f); // crear matriz identidad

	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotar el rectangulo horizontalmente
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // rotar el rectangulo para que se vea como en la imagen
	setModelMat(model); 
}