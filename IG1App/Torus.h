#ifndef H_Torus_H
#define H_torus_H

#include "SingleColorEntity.h"
class Torus :
    public SingleColorEntity
{
public:
    Torus(GLdouble R, GLdouble r, GLuint nPoints = 40, GLuint nSamples = 40);
};

#endif H_Torus_H

