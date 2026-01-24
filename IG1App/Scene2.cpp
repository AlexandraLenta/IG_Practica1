#include "Scene2.h"

Scene2::Scene2() : Scene() {

}

void Scene2::init() {
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	//gObjects.push_back(new RGBTriangle(200));

	gObjects.push_back(new RGBRectangle(200, 100));
}
