#include "Scene5.h"
#include "Torus.h"

void Scene5::init() {
	Scene::init();

	Torus* torus = new Torus(100, 50);
	gObjects.push_back(torus);
}

