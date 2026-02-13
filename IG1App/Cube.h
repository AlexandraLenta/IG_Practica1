#ifndef _H_Cube_H_
#define _H_Cube_H_

#include "SingleColorEntity.h"

class Cube : public SingleColorEntity
{
public:
	explicit Cube(GLdouble length, glm::vec4 color = { 0, 0, 0, 1 });
	~Cube();
	void render(const glm::mat4& modelViewMat) const override;
	

private:
	glm::vec4 mColor;
};

#endif _H_Cube_H_