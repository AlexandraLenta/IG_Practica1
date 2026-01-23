#pragma once
#include "SingleColorEntity.h"
class RegularPolygon : public SingleColorEntity 
{
public:
	explicit RegularPolygon(GLuint num, GLdouble r, glm::vec4 color);
};

