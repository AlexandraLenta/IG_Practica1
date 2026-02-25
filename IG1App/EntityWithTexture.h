#ifndef _H_EntityWithTexture_H_
#define _H_EntityWithTexture_H_
#include "Entity.h"
#include "Texture.h"

class EntityWithTexture : public EntityWithColors
{
public:
	EntityWithTexture(Texture* tex = nullptr, bool modulate = false);
	~EntityWithTexture();
	void render(glm::mat4 const& modelViewMat) const override;
	void setTexture(Texture* tex) { mTexture = tex; }

protected:
	Texture* mTexture = nullptr;
	bool mModulate = false;
};

#endif _H_EntityWithTexture_H_

