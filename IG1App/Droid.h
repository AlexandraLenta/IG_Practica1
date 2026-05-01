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
    void render(const glm::mat4& modelViewMat) const override;

private:
    SpotLight* mSpotLight;

    void createHead(GLfloat radius);
    void createLight(GLfloat radius);


};

#endif H_Droid_H