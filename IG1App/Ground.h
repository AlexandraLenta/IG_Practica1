#ifndef _H_Ground_H_
#define _H_Ground_H_

#include "Entity.h"
#include "EntityWithTexture.h"

class Ground : public EntityWithTexture
{
public:
    explicit Ground(GLdouble w, GLdouble h, Texture* tex);
};

#endif _H_Ground_H_

