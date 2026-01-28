#pragma once
#include "Entity.h"

class RGBRectangle : public EntityWithColors
{
public:
	RGBRectangle(GLdouble w, GLdouble h);
	void render(glm::mat4 const& modelViewMat) const override;
};

