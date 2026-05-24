#ifndef H_Scene7_H
#define H_Scene7_H

#include "Scene.h"
class Scene7 :
    public Scene
{
public:
    Scene7(Camera* c) : Scene(c) {}
    void init() override;
};

#endif H_Scene7_H
