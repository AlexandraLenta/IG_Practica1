#include "Scene4.h"
#include "Ground.h"
#include "BoxOutline.h"
#include "Star3D.h"

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

	// variables
	float groundW = 200;
	float groundH = 200;
	float starRadius = 150;
	float starZ = 150;
	float pointNr = 8;

	//gObjects.push_back(new Ground(groundW, groundH, ground));
	//gObjects.push_back(new BoxOutline(groundW, boxTex, boxInsideTex));
	gObjects.push_back(new Star3D(starRadius, pointNr, starZ));
}