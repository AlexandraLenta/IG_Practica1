#ifndef H_Scene9_H
#define H_Scene9_H

#include "Scene.h"
class Scene9 :
    public Scene
{
public:

    Scene9(Camera* c) : Scene(c) {}
    void init() override;
};

#endif

