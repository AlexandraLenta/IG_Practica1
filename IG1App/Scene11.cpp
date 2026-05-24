#include "Scene11.h"
#include "Disk.h"
void
Scene11::init() {
	Scene::init();
	GLfloat outerRadius = 50.f;
	GLfloat innerRadius = 20.f;
	gObjects.push_back(new Disk(outerRadius, outerRadius/2.f, 20, 20, {0, 0, 0, 1.0}));
	gObjects.push_back(new Disk(innerRadius, innerRadius / 2.f, 20, 20, { 1.0, 1.0, 0.0, 1.0 }));
	gObjects.push_back(new Disk(outerRadius - (outerRadius - innerRadius) / 2.f, 3.f * outerRadius / 4.f - innerRadius / 4.f, 20, 20, { 1.0, 1.0, 0.0, 1.0 }));
}