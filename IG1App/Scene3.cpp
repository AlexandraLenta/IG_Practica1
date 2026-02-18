#include "Scene3.h"
#include "RGBCube.h"
#include "Cube.h"

Scene3::Scene3() : Scene() {

}

void Scene3::init()
{
	Scene::init();
	gObjects.push_back(new RGBCube(100.0));
}

