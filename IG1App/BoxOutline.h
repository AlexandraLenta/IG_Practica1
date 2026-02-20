#ifndef _H_BoxOutline_H_
#define _H_BoxOutline_H_
#include "EntityWithTexture.h"
class BoxOutline :
    public EntityWithTexture
{
public:
    explicit BoxOutline(GLdouble length, Texture* tex);
};

#endif _H_BoxOutline_H_