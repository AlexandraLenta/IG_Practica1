#ifndef H_ColorMaterialEntity_H
#define H_ColorMaterialEntity_H

#include "SingleColorEntity.h"
class ColorMaterialEntity :
    public SingleColorEntity
{
public:
    ColorMaterialEntity(glm::vec4 color = { 1.0, 1.0, 1.0, 1.0 });
};

#endif H_ColorMaterialEntity_H