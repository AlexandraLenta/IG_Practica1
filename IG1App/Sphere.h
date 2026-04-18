#ifndef H_Sphere_H
#define H_Sphere_H

#include "ColorMaterialEntity.h"
class Sphere :
    public ColorMaterialEntity
{
public:
    Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians);
};

#endif H_Sphere_H