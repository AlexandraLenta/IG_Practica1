#include "Scene7.h"
#include "Sphere.h"

void Scene7::init() {
	Scene::init();
	Sphere* s = new Sphere(100, 10, 40);
	gObjects.push_back(s);
}
