#ifndef H_RGBCube_H
#define H_RGBCube_H

#include "Entity.h"

class RGBCube : public EntityWithColors
{
public:
	explicit RGBCube(GLdouble length);
	void update() override;

private:
	GLfloat angle = 0;
	GLdouble length;
	glm::vec3 axis = { 1.0, 0.0, 0.0 };
	glm::vec3 position;

	void rotate(GLfloat angle);
};

#endif H_RGBCube_H