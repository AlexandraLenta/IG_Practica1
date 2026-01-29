#include "Cube.h"
#include "Mesh.h"

Cube::Cube(GLdouble length, glm::vec4 color)
	: SingleColorEntity(color)
{
	mMesh = Mesh::generateCube(length);
}
