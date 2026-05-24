#ifndef H_Scene6_H
#define H_Scene6_H

#include "Scene.h"
class Scene6 :
    public Scene
{
public:
    Scene6(Camera* c) : Scene(c) {}
    void init() override;
};

#endif H_Scene6_H

