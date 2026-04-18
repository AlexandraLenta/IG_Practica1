#ifndef H_Disk_H
#define H_Disk_H

#include "ColorMaterialEntity.h"
class Disk :
    public ColorMaterialEntity
{
public:
    Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples);
};

#endif H_Disk_H