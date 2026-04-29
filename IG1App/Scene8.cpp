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

	PosLight* posLight = new PosLight(0);

	posLight->setPosition(glm::vec3(0, 2*sphereRadius, 0));

	posLight->setAmb(glm::vec3(0.2f, 0.2f, 0.2f));
	posLight->setDiff(glm::vec3(0.7f, 0.7f, 0.7f));
	posLight->setSpec(glm::vec3(0.1f, 0.1f, 0.1f));
	gLights.push_back(posLight);

	SpotLight* spotLight = new SpotLight(glm::vec3(0.0f, sphereRadius, sphereRadius * 2.0f), 0);

	spotLight->setAmb({ 0.25, 0.25, 0.25 });
	spotLight->setDiff({ 0.6, 0.6, 0.6 });
	spotLight->setSpec({ 0.0, 0.2, 0.0 });
	gLights.push_back(spotLight);

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
	// direccion en la que mira
	// la matriz de posicion tiene esta estructura
	// | Xx  Yx  Zx  Tx |
	// | Xy  Yy  Zy  Ty |
	// | Xz  Yz  Zz  Tz |
	// |  0   0   0   1 |
	// cogemos la primera columna, la de X, porque el droid original mira en direccion Z,
	// por lo tanto queremos rotarlo alrededor del X
	glm::vec3 facingDir = glm::normalize(glm::vec3(globalMat[0]));

	// rotamos alrededor de donde esta mirando ahora
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(2.0f), facingDir);
	mFictionalNode->setModelMat(rot * mFictionalNode->modelMat());
}

void 
Scene8::rotate() {
	// rotar sobre el eje y
	mDroid->setModelMat(glm::rotate(glm::mat4(1.0f), glm::radians(2.0f), glm::vec3(0, 1, 0)) * mDroid->modelMat());
}

void Scene8::togglePosLight()
{
	if (gLights.size() > 1)
		gLights[1]->setEnabled(!gLights[1]->enabled());
}