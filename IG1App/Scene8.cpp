#include "Scene8.h"
#include "Sphere.h"
#include "Droid.h"

void
Scene8::init() {
	Scene::init();

	GLfloat sphereRadius = 300;
	GLfloat droidRadius = 25;
	glm::vec4 colorGranate = { 0.67, 0.13, 0.28, 1.0 };
	Texture* droidTex = texLoader->getTexture("container.jpg");

	Sphere* planet = new Sphere(sphereRadius, 40, 40, colorGranate);
	gObjects.push_back(planet);

	Droid* droid = new Droid(droidRadius, droidTex);
	droid->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0, sphereRadius + droidRadius, 0)));
	gObjects.push_back(droid);

}

void Scene8::setGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}