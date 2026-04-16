#include "ColorMaterialEntity.h"

ColorMaterialEntity::ColorMaterialEntity(glm::vec4 color) : SingleColorEntity(color) {
	mShader = Shader::get("simple_light");
}