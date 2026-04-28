#ifndef H_Scene8_H
#define H_Scene8_H

#include "Scene.h"

class CompoundEntity;
class Droid;

class Scene8 :
    public Scene
{
public:
    void init() override;
    void setGL() override;

    void orbit() override;
    void rotate() override;
    void togglePosLight();

private:
    CompoundEntity* mFictionalNode;
    Droid* mDroid;
};

#endif H_Scene8_H