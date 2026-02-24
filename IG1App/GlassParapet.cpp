#include "GlassParapet.h"

GlassParapet::GlassParapet(GLdouble length, Texture* tex) : EntityWithTexture(tex) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}

void
GlassParapet::render(glm::mat4 const& modelViewMat) const {
	glEnable(GL_BLEND);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	EntityWithTexture::render(modelViewMat);
	
	glDisable(GL_BLEND);
}
