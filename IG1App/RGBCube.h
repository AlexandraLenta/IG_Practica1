#ifndef H_RGBCube_H
#define H_RGBCube_H

#include "Entity.h"

class RGBCube : public EntityWithColors
{
public:
	explicit RGBCube(GLdouble length);
	~RGBCube();
	void update() override;

private:
	GLfloat angle;
	GLdouble length;
	glm::vec3 axis;
	glm::vec3 position;

	void rotate(GLfloat angle);
};

#endif H_RGBCube_H