#ifndef H_Disk_H
#define H_Disk_H

#include "ColorMaterialEntity.h"
class Disk :
    public ColorMaterialEntity
{
public:
    Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples, glm::vec4 color);
};

#endif H_Disk_H