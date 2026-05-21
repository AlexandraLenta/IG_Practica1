#ifndef H_ColorMaterialEntity_H
#define H_ColorMaterialEntity_H

#include "EntityWithMaterial.h"
class ColorMaterialEntity :
    public EntityWithMaterial
{
public:
    ColorMaterialEntity(glm::vec3 color);
};

#endif H_ColorMaterialEntity_H