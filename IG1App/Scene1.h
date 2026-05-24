#ifndef H_Scene_H
#define H_Scene_H

#include "Scene.h"

class Scene1 : public Scene
{
public:
	Scene1(Camera* c) : Scene(c) {}
	void init() override;
};

#endif H_Scene_H