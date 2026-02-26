#ifndef H_Photo_H
#define H_Photo_H

#include "EntityWithTexture.h"
class Photo :
    public EntityWithTexture
{
public:
    Photo(GLdouble length);
    ~Photo();
    void update() override;
    GLuint* getImg();
private:
    GLdouble length;
    int width, height;
};

#endif H_Photo_H