#ifndef H_Scene4_H
#define H_Scene4_H

#include "Scene.h"
#include "Photo.h"
#include "TextureLoader.h"

class Scene4 :
    public Scene
{
    std::vector<Abs_Entity*> transparentObj;
public:
    ~Scene4();
    void init() override;
    void render(Camera const& cam) const override;

    void load() override;
    void unload() override;
};

#endif H_Scene4_H