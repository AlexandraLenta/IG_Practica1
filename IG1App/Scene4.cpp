#include "Scene4.h"
#include "Ground.h"
#include "BoxOutline.h"
#include "Star3D.h"
#include "Box.h"
#include "GlassParapet.h"
#include "Grass.h"
#include "Photo.h"
#include "TextureLoader.h"

#include <algorithm>
#include <map>

void
Scene4::init() {
	Scene::init();

	// cargar las texturas
	Texture* groundTex = texLoader->getTexture("baldosaC.png");
	Texture* boxTex = texLoader->getTexture("papelE.png");
	Texture* boxInsideTex = texLoader->getTexture("container.jpg");
	Texture* starTex = texLoader->getTexture("rueda.png");
	Texture* glass = texLoader->getTexture("windowC.png", 150);
	Texture* grassTex = texLoader->getTexture("grass.png");

	// variables
	float groundX = 200;
	float groundY = 100;
	float groundZ = 200;
	float starRadius = 40;
	float boxSize = 40;
	float starZ = 40;
	float pointNr = 8;
	float floorHeight = 25;
	float starFloorHeight = 10;
	float offset = 150;
	float scale = 0.2f;
	float photoSize = 50;
	float boxPosX = -groundX / 2 + offset;
	float boxPosZ = -groundZ / 2 + offset;

	gObjects.push_back(new Ground(groundX, groundZ, groundTex));

	Box* box = new Box(boxSize, boxTex, boxInsideTex);
	box->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(boxPosX, floorHeight, boxPosZ)));
	gObjects.push_back(box);

	Star3D* star = new Star3D(starRadius*scale, pointNr, starZ*scale, starTex);
	glm::vec3(boxPosX, floorHeight, boxPosZ);
	gObjects.push_back(star);
	glm::mat4 matStar = glm::mat4(1.0f);
	matStar = glm::translate(matStar, glm::vec3(boxPosX, floorHeight, boxPosZ));
	gObjects.back()->setModelMat(matStar);

	GlassParapet* glassP = new GlassParapet(groundX, glass);
	glassP->setModelMat(glm::scale(glm::mat4(1.0f), glm::vec3(1, 0.5, 1)));
	gObjects.push_back(glassP);
	transparentObj.push_back(glassP);

	Grass* grass = new Grass(starRadius, grassTex);
	grass->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-groundX / 4, floorHeight, -groundX / 4)));
	gObjects.push_back(grass);
	transparentObj.push_back(grass);

	Photo* photo = new Photo(photoSize);
	photo->setModelMat(glm::rotate(photo->modelMat(), glm::radians(-90.0f), glm::vec3(1, 0, 0)) * glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 10)));
	gObjects.push_back(photo);
}

void Scene4::render(Camera const& cam) const {
	//obj opacos
	for (auto obj : gObjects) {
		bool isTransparent = false;
		for (auto t : transparentObj) 
		{
			if (obj == t) {
				isTransparent = true;
				break;
			}
		}
		if (!isTransparent) {
			obj->render(cam.viewMat());
		}

	}

	//ordenar transparentes
	std::map<float, EntityWithTexture*, std::greater<float>> sorted;
	glm::vec3 camPos = cam.getEye();
	for (auto obj : transparentObj) {

		glm::vec3 pos = glm::vec3(obj->modelMat()[3]);
		float dist = glm::distance(camPos, pos);
		//evitar dupes
		while (sorted.find(dist) != sorted.end()) 
		{
			dist += 0.0001f;
		}
		sorted[dist] = obj;
	}

	//render transp
	for (auto& pair : sorted) {
		pair.second->render(cam.viewMat());
	}
}