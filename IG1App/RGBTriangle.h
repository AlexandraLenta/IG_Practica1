#ifndef H_RGBTriangle_H
#define H_RGBTriangle_H

#include "Entity.h"

class RGBTriangle : public EntityWithColors
{
public:
	explicit RGBTriangle(GLdouble r);
	~RGBTriangle();
	explicit RGBTriangle(GLdouble r, GLdouble pos);

	void update() override;
	void rotate(GLdouble l, GLdouble g);

private:
	float position;
	float localAngle = 0;
	float globalAngle = 0;
};

#endif H_RGBTriangle_H