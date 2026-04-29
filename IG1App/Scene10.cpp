#include "Scene10.h"
#include "Sphere.h"

void Scene10::init() {
	Scene::init();

    GLdouble r = 50.0;
    Sphere* yellowPlanet = new Sphere(r, 15, 15, { 1.0f, 1.0f, 0.0f});

    gObjects.push_back(yellowPlanet);
    yellowPlanet->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, r*2)));


    Sphere* goldPlanet = new Sphere(r, 15, 15, { 1.0f, 1.0f, 0.0f});

    gObjects.push_back(goldPlanet);
    goldPlanet->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(2 * r, 0, 0)));

    Material m;
    m.setAmb(glm::vec3(0.2f, 0.2f, 0.0f));
    m.setDiff(glm::vec3(0.7f, 0.5f, 0.0f));
    m.setSpec(glm::vec3(0.6f, 0.5f, 0.3f));
    m.setExp(32);
    goldPlanet->setMaterial(m);

}