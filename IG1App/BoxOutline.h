#ifndef _H_BoxOutline_H_
#define _H_BoxOutline_H_
#include "EntityWithTexture.h"
class BoxOutline :
    public EntityWithTexture
{
public:
    explicit BoxOutline(GLdouble length, Texture* texOut, Texture* texIn);
    void render(glm::mat4 const& modelViewMat) const override;
private:
    Texture* textureInside;
};

#endif _H_BoxOutline_H_