#include "Scene1.h"

void Scene1::init() {
	Scene::init();

	gObjects.push_back(new RegularPolygon(6, 100, { 1.0, 0.0, 1.0, 1.0 }));
	gObjects.push_back(new RegularPolygon(200, 100, { 1.0, 1.0, 0.0, 1.0 }));
}

