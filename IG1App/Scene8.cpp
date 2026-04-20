#include "Scene8.h"
#include "Sphere.h"
#include "Droid.h"

void
Scene8::init() {
	Scene::init();

	// variables
	GLfloat sphereRadius = 300;
	GLfloat droidRadius = sphereRadius/12;
	glm::vec4 colorGranate = { 0.67, 0.13, 0.28, 1.0 };

	// textura para el droid
	Texture* droidTex = texLoader->getTexture("container.jpg");

	// planeta
	Sphere* planet = new Sphere(sphereRadius, 40, 40, colorGranate);
	gObjects.push_back(planet);

	// nodo ficticio para el movimiento del droid
	mFictionalNode = new CompoundEntity();
	
	mDroid = new Droid(droidRadius, droidTex);
	mDroid->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0, sphereRadius + droidRadius, 0)));
	
	mFictionalNode->addEntity(mDroid);

	gObjects.push_back(mFictionalNode);

}

void Scene8::setGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}

void
Scene8::orbit() {
	// rotacion de droide y del nodo global
	glm::mat4 globalMat = mFictionalNode->modelMat() * mDroid->modelMat();
	// coger donde mira
	glm::vec3 facingDir = glm::normalize(glm::vec3(globalMat[0]));


}

void 
Scene8::rotate() {
	// rotar sobre el eje y
	mDroid->setModelMat(glm::rotate(glm::mat4(1.0f), glm::radians(2.0f), glm::vec3(0, 1, 0)) * mDroid->modelMat());
}