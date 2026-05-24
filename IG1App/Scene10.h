#ifndef H_SCENE10_H
#define H_SCENE10_H

#include "Scene.h"
class Scene10 :
    public Scene
{
public:
    Scene10(Camera* c) : Scene(c) {}

    void init() override;
};

#endif