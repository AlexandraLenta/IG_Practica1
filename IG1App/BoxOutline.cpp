#include "BoxOutline.h"

BoxOutline::BoxOutline(GLdouble length, Texture* tex) : EntityWithTexture(tex) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}