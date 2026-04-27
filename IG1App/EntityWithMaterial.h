#ifndef H_EntityWithMaterial_H
#define H_EntityWithMaterial_H
#include "Entity.h"
#include "Material.h"

class EntityWithMaterial :
    public Abs_Entity
{
public:
    Material mMaterial;

    EntityWithMaterial();
    void render(const glm::mat4& modelViewMat) const override;
};

#endif

