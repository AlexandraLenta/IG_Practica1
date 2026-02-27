#ifndef H_Scene4_H
#define H_Scene4_H

#include "Scene.h"
#include "Photo.h"
#include "TextureLoader.h"

class Scene4 :
    public Scene
{
public:
    void init() override;

private:
    TextureLoader* texLoader;
};

#endif H_Scene4_H