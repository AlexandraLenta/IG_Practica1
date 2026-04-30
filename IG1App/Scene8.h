#ifndef H_Scene8_H
#define H_Scene8_H

#include "Scene.h"

class CompoundEntity;
class Droid;

class Scene8 :
    public Scene
{
public:
    ~Scene8();
    void init() override;
    void setGL() override;

    void orbit() override;
    void rotate() override;

    void togglePosLight() override;
    void toggleSpotLight() override;

    void uploadLights(const Camera& cam) const override;

    void unload() override;

private:
    CompoundEntity* mFictionalNode;
    Droid* mDroid;

    PosLight* mPosLight;
    SpotLight* mSpotLight;
};

#endif H_Scene8_H