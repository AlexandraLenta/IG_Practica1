#ifndef H_Scene3_H
#define H_Scene3_H

#include "Scene.h"

class Scene3 : public Scene
{
public:
	Scene3(Camera* c) : Scene(c) {}
	void init() override;
};

#endif H_Scene3_H