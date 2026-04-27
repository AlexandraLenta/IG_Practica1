#ifndef H_ColorMaterialEntity_H
#define H_ColorMaterialEntity_H

#include "EntityWithMaterial.h"
class ColorMaterialEntity :
    public EntityWithMaterial
{
public:
    ColorMaterialEntity(glm::vec4 color = { 1.0, 1.0, 1.0, 1.0 });
    void render(const glm::mat4& modelViewMat) const override;

    static void toggleShowNormals();

private:
    Shader* mNormalsShader = nullptr;
    static bool mShowNormals;
};

#endif H_ColorMaterialEntity_H