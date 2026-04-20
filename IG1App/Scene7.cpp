#include "Scene7.h"
#include "Sphere.h"
#include "SphereWithTexture.h"
#include "Cone.h"
#include "Disk.h"

void Scene7::init() {
	Scene::init();
	//Sphere* s = new Sphere(100, 10, 40);
	//gObjects.push_back(s);

	Texture* sphereTex = texLoader->getTexture("container.jpg");

	SphereWithTexture* s = new SphereWithTexture(100, 10, 40, sphereTex);
	gObjects.push_back(s);

	//Cone* c = new Cone(100, 80, 40, 5, 20);
	//gObjects.push_back(c);

	//Disk* d = new Disk(100, 30, 10, 10);
	//gObjects.push_back(d);
}
