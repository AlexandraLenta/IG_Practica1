#ifndef H_Droid_H
#define H_Droid_H
#include "CompoundEntity.h"
#include "Light.h"

class Texture;

class Droid :
    public CompoundEntity
{
public:
    Droid(GLdouble radius, Texture* bodyTex);
    ~Droid();
    void toggleLight();
    

private:
    SpotLight* mSpotLight;

    void createHat();
    void createHead(GLfloat radius);
    void createLight(GLfloat radius);
};

#endif H_Droid_H