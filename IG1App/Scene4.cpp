#include "Scene4.h"
#include "Ground.h"
#include "BoxOutline.h"
#include "Star3D.h"
#include "Box.h"
#include "GlassParapet.h"
#include "Grass.h"
#include "Photo.h"
#include "BMPFileSaver.h"

void
Scene4::init() {
	Scene::init();

	// cargar las texturas
	Texture* groundTex = new Texture();
	groundTex->load("../assets/images/baldosaC.png");
	gTextures.push_back(groundTex);

	Texture* boxTex = new Texture();
	boxTex->load("../assets/images/papelE.png");
	gTextures.push_back(boxTex);

	Texture* boxInsideTex = new Texture();
	boxInsideTex->load("../assets/images/container.jpg");
	gTextures.push_back(boxInsideTex);

	Texture* starTex = new Texture();
	starTex->load("../assets/images/rueda.png");
	gTextures.push_back(starTex);

	Texture* glass = new Texture();
	glass->load("../assets/images/windowC.png", 150);
	gTextures.push_back(glass);

	Texture* grassTex = new Texture();
	grassTex->load("../assets/images/grass.png");
	gTextures.push_back(grassTex);

	// variables
	float groundX = 200;
	float groundY = 100;
	float groundZ = 200;
	float starRadius = 40;
	float boxSize = 40;
	float starZ = 40;
	float pointNr = 8;
	float floorHeight = 20;
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

	Star3D* star = new Star3D(starRadius, pointNr, starZ, starTex);
	star->transformModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(starPosX, floorHeight, starPosZ)) * glm::scale(glm::mat4(1.0f),
		glm::vec3(scale)));
	gObjects.push_back(star);

	gObjects.push_back(new GlassParapet(groundX, groundY, groundZ, glass));

	Grass* grass = new Grass(starRadius, grassTex);
	grass->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-groundX / 4, floorHeight, -groundX / 4)));
	gObjects.push_back(grass);

	photoObj = new Photo(photoSize);
	photoObj->setModelMat(glm::rotate(photoObj->modelMat(), glm::radians(-90.0f), glm::vec3(1, 0, 0)) * glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 10)));
	gObjects.push_back(photoObj);
}

void
Scene4::saveImage() {
	BMPFileSaver::saveToBmp(photoObj->getImg());
}