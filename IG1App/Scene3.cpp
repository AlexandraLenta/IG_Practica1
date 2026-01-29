#include "Scene3.h"
#include "Cube.h"

void Scene3::init()
{
		setGL();


		//glEnable(GL_CULL_FACE);

		gObjects.push_back(new RGBAxes(400.0));
		gObjects.push_back(new Cube(100.0, { 0, 0, 0, 1 }));
	
}

