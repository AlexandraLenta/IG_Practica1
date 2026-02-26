#ifndef H_Scene4_H
#define H_Scene4_H

#include "Scene.h"
#include "Photo.h"

class Scene4 :
    public Scene
{
public:
    void init() override;
    void saveImage() override;

private:
    Photo* photoObj;
};

#endif H_Scene4_H