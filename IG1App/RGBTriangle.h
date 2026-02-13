#ifndef H_RGBTriangle_H
#define H_RGBTriangle_H

#include "Entity.h"

class RGBTriangle : public EntityWithColors
{
public:
	explicit RGBTriangle(GLdouble r);
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

#endif H_RGBTriangle_H