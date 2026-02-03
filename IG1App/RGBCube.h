#pragma once
#include "Entity.h"

class RGBCube : public EntityWithColors
{
public:
	RGBCube(GLdouble length);
	~RGBCube();
	void update() override;

private:
	GLfloat angle;
	GLdouble length;
	glm::vec3 axis;
	glm::vec3 position;

	void rotate(GLfloat angle);
};

