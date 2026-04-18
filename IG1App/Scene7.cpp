#include "Scene7.h"
#include "Sphere.h"
#include "Cone.h"

void Scene7::init() {
	Scene::init();
	/*Sphere* s = new Sphere(100, 10, 40);
	gObjects.push_back(s);*/

	Cone* c = new Cone(100, 80, 30, 10,10);
	gObjects.push_back(c);
}
