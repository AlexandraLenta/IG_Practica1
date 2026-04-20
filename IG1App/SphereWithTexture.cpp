#include "SphereWithTexture.h"
#include "IndexMesh.h"

SphereWithTexture::SphereWithTexture(GLfloat radius, GLuint nParallels, GLuint nMeridians, Texture* tex) : EntityWithTexture(tex) {
	mMesh = IndexMesh::generateSphere(radius, nParallels, nMeridians);
}