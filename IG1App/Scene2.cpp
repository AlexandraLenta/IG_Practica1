#include "Scene2.h"
#include "RGBRectangle.h"
#include "RGBTriangle.h"
#include "RegularPolygon.h"

void Scene2::init() {
	Scene::init();

	float circleRadius = 200;

	gObjects.push_back(new RGBRectangle(circleRadius * sqrt(2), circleRadius * sqrt(2)));
	RGBTriangle* tr = new RGBTriangle(50, circleRadius);
	tr->setModelMat(glm::translate(tr->modelMat(), glm::vec3(circleRadius, 0.0, 0.0)));
	gObjects.push_back(tr);
	gObjects.push_back(new RegularPolygon(100, circleRadius, {1.0, 0.0, 1.0, 1.0}));
}