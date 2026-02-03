#pragma once
#include "Entity.h"

class SingleColorEntity : public Abs_Entity
{
public:
	SingleColorEntity(glm::vec4);
	~SingleColorEntity();

	glm::vec4 getColor() const;
	void setColor(glm::vec4);
	void render(const glm::mat4& modelViewMat) const override;

private:
	glm::vec4 mColor;
};

