#pragma once
#include "EntityWithTexture.h"
class Photo :
    public EntityWithTexture
{
public:
    Photo(GLdouble length);
    ~Photo();
    void update() override;
private:
    GLdouble length;
};