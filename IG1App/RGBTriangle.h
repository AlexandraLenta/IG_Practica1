#pragma once
#include "Entity.h"

class RGBTriangle : public EntityWithColors
{
public:
	RGBTriangle(GLdouble r, GLdouble posX = 0, GLdouble posY = 0, GLdouble posZ = 0);
	~RGBTriangle();

	void update() override;
	void rotate(GLdouble d);

private:
	glm::vec3 position;
	float radius;
	glm::vec3 originalDisplacement;
	float angle = 0;
};

