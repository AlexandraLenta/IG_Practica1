#include "GlassParapet.h"

GlassParapet::GlassParapet(GLdouble length, Texture* tex) : EntityWithTexture(tex) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}