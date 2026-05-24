#ifndef H_Scene2_H
#define H_Scene2_H

#include "Scene.h"

class Scene2 : public Scene
{
public:
	Scene2(Camera* c) : Scene(c) {}
	void init() override;
};

#endif H_Scene2_H