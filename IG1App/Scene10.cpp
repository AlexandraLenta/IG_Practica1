#include "Scene10.h"
#include "Sphere.h"

void Scene10::init() {
	Scene::init();

    GLdouble r = 20.0;
    Sphere* yellowPlanet = new Sphere(r, 10, 10, { 1.0f, 1.0f, 0.0f, 1.0f });

    gObjects.push_back(yellowPlanet);
    yellowPlanet->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-2 * r, 0, 0)));


    Sphere* goldPlanet = new Sphere(r, 10, 10, { 1.0f, 1.0f, 0.0f, 1.0f });

    gObjects.push_back(goldPlanet);
    goldPlanet->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(2 * r, 0, 0)));

}