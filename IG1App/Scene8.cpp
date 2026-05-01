#include "Scene8.h"
#include "Sphere.h"
#include "Droid.h"

Scene8::~Scene8() {
	delete mSpotLight;
	delete mPosLight;

	mSpotLight = nullptr;
	mPosLight = nullptr;
}

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

	mPosLight = new PosLight(0);

	mPosLight->setPosition(glm::vec3(0, sphereRadius * 1.5f, 0));

	mPosLight->setAmb(glm::vec3(0.2f, 0.2f, 0.2f));
	mPosLight->setDiff(glm::vec3(0.7f, 0.7f, 0.7f));
	mPosLight->setSpec(glm::vec3(0.1f, 0.1f, 0.1f));

	mSpotLight = new SpotLight(glm::vec3(0.0f, 0.0f, sphereRadius * 1.2f), 0);

	mSpotLight->setAmb({ 0.25, 0.25, 0.25 });
	mSpotLight->setDiff({ 0.6, 0.6, 0.6 });
	mSpotLight->setSpec({ 0.0, 0.2, 0.0 });
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
	if (mPosLight)
		mPosLight->setEnabled(!mPosLight->enabled());
}

void Scene8::toggleSpotLight()
{
	if (mSpotLight)
		mSpotLight->setEnabled(!mSpotLight->enabled());
}

void Scene8::uploadLights(const Camera& cam) const {
	Scene::uploadLights(cam);

	Shader* sh = Shader::get("light");
	sh->use();

	mSpotLight->upload(*sh, cam.viewMat());
	mPosLight->upload(*sh, cam.viewMat());
}

void Scene8::unload() {
	Scene::unload();

	mSpotLight->unload(*Shader::get("light"));
	mPosLight->unload(*Shader::get("light"));
}

void Scene8::handleKey(unsigned int key) {
	switch (key) {
	case 't':
		togglePosLight();
		break;
	case 'y':
		toggleSpotLight();
		break;
	case 'h':
		toggleDroidLight();
		break;
	case 'f':
		rotate();
		break;
	case 'g':
		orbit();
		break;
	default:
		break;
	}
}

void Scene8::toggleDroidLight() {
	mDroid->toggleLight();
}