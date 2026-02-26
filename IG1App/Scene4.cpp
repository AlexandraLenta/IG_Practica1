#include "Scene4.h"
#include "Ground.h"
#include "BoxOutline.h"
#include "Star3D.h"
#include "Box.h"
#include "GlassParapet.h"
#include "Grass.h"
#include "Photo.h"

void
Scene4::init() {
	Scene::init();

	// cargar las texturas
	Texture* ground = new Texture();
	ground->load("../assets/images/baldosaC.png");
	gTextures.push_back(ground);

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
	float starZ = 40;
	float pointNr = 8;
	float y = 20;
	float offset = 150;
	float scale = 0.3f;

	gObjects.push_back(new Ground(groundX, groundZ, ground));

	Box* box = new Box(starRadius, boxTex, boxInsideTex);
	box->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-groundX / 2 + offset, y, -groundZ / 2 + offset)));
	gObjects.push_back(box);

	Star3D* star = new Star3D(starRadius, pointNr, starZ, starTex);
	star->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-groundX / 2 + offset, y, -groundZ / 2 + offset)) * glm::scale(glm::mat4(1.0f),
		glm::vec3(scale)));
	gObjects.push_back(star);

	gObjects.push_back(new GlassParapet(groundX, groundY, groundZ, glass));

	Grass* grass = new Grass(starRadius, grassTex);
	grass->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-groundX / 4, y, -groundX / 4)));
	gObjects.push_back(grass);

	//Photo* photo = new Photo(300);
	//photo->setModelMat(glm::rotate(photo->modelMat(), glm::radians(-90.0f), glm::vec3(1, 0, 0)));
	//gObjects.push_back(photo);
}

//void
//Scene4::saveImage() {
//
//}