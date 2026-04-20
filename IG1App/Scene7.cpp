#include "Scene7.h"
#include "Sphere.h"
#include "SphereWithTexture.h"
#include "Cone.h"
#include "Disk.h"
#include "Droid.h"

void Scene7::init() {
	Scene::init();

	Droid* d = new Droid(100, texLoader->getTexture("container.jpg"));
	gObjects.push_back(d);

}
