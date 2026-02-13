#include "Scene2.h"

Scene2::Scene2() : Scene() {}

void Scene2::init() {
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	gObjects.push_back(new RGBRectangle(200 * sqrt(2), 200*sqrt(2)));
	RGBTriangle* tr = new RGBTriangle(50);
	tr->setModelMat(glm::translate(tr->modelMat(), glm::vec3(200, 0.0, 0.0)));
	gObjects.push_back(tr);
	gObjects.push_back(new RegularPolygon(100, 200, {1.0, 0.0, 1.0, 1.0}));
}

Scene2::~Scene2() {

}
