#pragma once
#include "Entity.h"

class RGBTriangle : public EntityWithColors
{
public:
	explicit RGBTriangle(GLdouble r, GLdouble posX = 0, GLdouble posY = 0, GLdouble posZ = 0);
	~RGBTriangle();

	void update() override;
	void rotate(GLdouble l, GLdouble g);

private:
	glm::vec3 position;
	float radius;
	glm::vec3 originalDisplacement;
	float localAngle = 0;
	float globalAngle = 0;
};

