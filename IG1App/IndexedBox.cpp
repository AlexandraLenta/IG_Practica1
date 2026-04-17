#include "IndexedBox.h"
#include "IndexMesh.h"

IndexedBox::IndexedBox(GLdouble l) : ColorMaterialEntity(glm::vec4(0, 1, 0, 1)){
	mMesh = IndexMesh::generateIndexedBox8(l);
}