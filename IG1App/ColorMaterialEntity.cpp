#include "ColorMaterialEntity.h"

ColorMaterialEntity::ColorMaterialEntity(glm::vec3 color) : EntityWithMaterial() {
    mMaterial = Material(color);
}

