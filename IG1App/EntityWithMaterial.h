#ifndef H_EntityWithMaterial_H
#define H_EntityWithMaterial_H
#include "Entity.h"
#include "Material.h"

class EntityWithMaterial :
    public Abs_Entity
{
public:

    EntityWithMaterial();
    void setMaterial(const Material& m) { mMaterial = m; };
    void render(const glm::mat4& modelViewMat) const override;

protected:
    Material mMaterial;
};

#endif

