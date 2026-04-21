#ifndef H_CompoundEntity_H
#define H_CompoundEntity_H
#include "Entity.h"

class CompoundEntity :
    public Abs_Entity
{
public:
    ~CompoundEntity();

    void addEntity(Abs_Entity* ae);

    void render(const glm::mat4& modelViewMat) const override;
    void update() override;
    void load() override;
    void unload() override;

protected:
    std::vector<Abs_Entity*> gObjects;
};

#endif H_CompoundEntity_H