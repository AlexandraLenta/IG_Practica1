#pragma once
#include "Entity.h"

class RGBRectangle : public EntityWithColors
{
public:
	RGBRectangle(GLdouble w, GLdouble h);
	~RGBRectangle();
	void render(glm::mat4 const& modelViewMat) const override;
};

