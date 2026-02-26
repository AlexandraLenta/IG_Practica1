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

	Texture* grass = new Texture();
	grass->load("../assets/images/grass.png");
	gTextures.push_back(grass);

	// variables
	float groundW = 200;
	float groundH = 200;
	float starRadius = 40;
	float starZ = 40;
	float pointNr = 8;

	gObjects.push_back(new Ground(groundW, groundH, ground));

	Box* box = new Box(starRadius, boxTex, boxInsideTex);
	box->setModelMat(glm::translate(glm::mat4(1.0f),glm::vec3(-groundW / 2 + 150, 20, -groundH / 2 + 150)));
	gObjects.push_back(box);

	Star3D* star = new Star3D(starRadius, pointNr, starZ, starTex);
	star->setModelMat(glm::translate(glm::mat4(1.0f),glm::vec3(-groundW / 2 + 150, 20, -groundH / 2 + 150))* glm::scale(glm::mat4(1.0f),
		glm::vec3(0.3f)));
	gObjects.push_back(star);

	gObjects.push_back(new GlassParapet(groundW, glass));

	Grass* hierba = new Grass(starRadius, grass);
	hierba->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-groundW / 4, 20, -groundW / 4)));
	gObjects.push_back(hierba);

	//gObjects.push_back(new BoxOutline(groundW, boxTex, boxInsideTex));
	//gObjects.push_back(new Star3D(starRadius, pointNr, starZ, starTex));
	//gObjects.push_back(new Box(starRadius, boxTex, boxInsideTex));
	//gObjects.push_back(new GlassParapet(boxSize, glass));
	//gObjects.push_back(new Grass(starRadius, grass));
	//Photo* photo = new Photo(300);
	//photo->setModelMat(glm::rotate(photo->modelMat(), glm::radians(-90.0f), glm::vec3(1, 0, 0)));
	//gObjects.push_back(photo);
}

//void
//Scene4::saveImage() {
//
//}