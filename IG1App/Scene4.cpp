#include "Scene4.h"
#include "Ground.h"

void
Scene4::init() {
	Scene::init();

	gObjects.push_back(new Ground(200, 150));
}