#ifndef H_Cone_H
#define H_Cone_H

#include "ColorMaterialEntity.h"
class Cone :
    public ColorMaterialEntity
{
public:
    Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples);
};

#endif H_Cone_H