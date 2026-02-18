#ifndef H_RGBRectangle_H
#define H_RGBRectangle_H

#include "Entity.h"

class RGBRectangle : public EntityWithColors
{
public:
	explicit RGBRectangle(GLdouble w, GLdouble h);

	void render(glm::mat4 const& modelViewMat) const override;
};

#endif H_RGBRectangle_H