#include "Scene3.h"
#include "Cube.h"

Scene3::Scene3() : Scene() {

}

void Scene3::init()
{
		setGL();

		gObjects.push_back(new RGBAxes(400.0));
		gObjects.push_back(new Cube(100.0, { 0, 0, 0, 1 }));
}

