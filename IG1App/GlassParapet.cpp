#include "GlassParapet.h"

GlassParapet::GlassParapet(GLdouble length, Texture* tex) : EntityWithTexture(tex) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}

void
GlassParapet::render(glm::mat4 const& modelViewMat) const {
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	EntityWithTexture::render(modelViewMat);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}