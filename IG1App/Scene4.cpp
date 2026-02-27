#include "Scene4.h"
#include "Ground.h"
#include "BoxOutline.h"
#include "Star3D.h"
#include "Box.h"
#include "GlassParapet.h"
#include "Grass.h"
#include "Photo.h"
#include "TextureLoader.h"

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
	float starPosX = boxPosX - 10;
	float starPosZ = boxPosZ - 10;

	gObjects.push_back(new Ground(groundX, groundZ, groundTex));

	Box* box = new Box(boxSize, boxTex, boxInsideTex);
	box->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(boxPosX, floorHeight, boxPosZ)));
	gObjects.push_back(box);

	Star3D* star = new Star3D(starRadius*scale, pointNr, starZ*scale, starTex, glm::vec3(starPosX, starFloorHeight, starPosZ));
	gObjects.push_back(star);

	gObjects.push_back(new GlassParapet(groundX, groundY, groundZ, glass));

	Grass* grass = new Grass(starRadius, grassTex);
	grass->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-groundX / 4, floorHeight, -groundX / 4)));
	gObjects.push_back(grass);

	Photo* photo = new Photo(photoSize);
	photo->setModelMat(glm::rotate(photo->modelMat(), glm::radians(-90.0f), glm::vec3(1, 0, 0)) * glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 10)));
	gObjects.push_back(photo);
}