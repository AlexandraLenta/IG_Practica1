#pragma once
#include "Entity.h"

class RGBCube : public EntityWithColors
{
public:
	RGBCube(GLdouble length);
	void update() override;
};

