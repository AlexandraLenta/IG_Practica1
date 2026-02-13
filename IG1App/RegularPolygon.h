#ifndef H_SingleColorEntity_H
#define H_SingleColorEntity_H

#include "SingleColorEntity.h"
class RegularPolygon : public SingleColorEntity 
{
public:
	explicit RegularPolygon(GLuint num, GLdouble r, glm::vec4 color = {0.0, 0.0, 0.0, 1.0});
	~RegularPolygon();
};

#endif H_SingleColor_H