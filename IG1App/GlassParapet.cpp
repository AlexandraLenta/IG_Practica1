#include "GlassParapet.h"

GlassParapet::GlassParapet(GLdouble length, Texture* tex) : EntityWithTexture(tex) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}

void
GlassParapet::render(glm::mat4 const& modelViewMat) const {
	glEnable(GL_BLEND);

	glBlendColor(0, 0, 0, 0.5f);
	
	glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

	EntityWithTexture::render(modelViewMat);

	glBlendFunc(GL_ONE, GL_ZERO);
	
	glDisable(GL_BLEND);
}
