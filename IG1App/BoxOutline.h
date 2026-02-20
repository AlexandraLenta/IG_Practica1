#ifndef _H_BoxOutline_H_
#define _H_BoxOutline_H_
#include "SingleColorEntity.h"
class BoxOutline :
    public SingleColorEntity
{
public:
    explicit BoxOutline(GLdouble length);
    void render(const glm::mat4& modelViewMat) const override;
};

#endif _H_BoxOutline_H_