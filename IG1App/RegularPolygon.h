#ifndef H_RegularPolygon_H
#define H_RegularPolygon_H

#include "SingleColorEntity.h"
class RegularPolygon : public SingleColorEntity 
{
public:
	explicit RegularPolygon(GLuint num, GLdouble r, glm::vec4 color = {0.0, 0.0, 0.0, 1.0});
};

#endif H_RegularPolygon_H
