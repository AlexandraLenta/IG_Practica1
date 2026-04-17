#include "Scene6.h"
#include "IndexedBox.h"

void Scene6::init() {
	Scene::init();

	IndexedBox* box = new IndexedBox(100);
	gObjects.push_back(box);
}
