#include "Scene1.h"

Scene1::Scene1() : Scene() {

}

void Scene1::init() {
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	gObjects.push_back(new RegularPolygon(7, 100, { 1.0, 0.0, 1.0, 1.0 }));
	gObjects.push_back(new RegularPolygon(200, 100, { 1.0, 1.0, 0.0, 1.0 }));
}
