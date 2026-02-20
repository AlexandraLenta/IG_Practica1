#include "Scene4.h"
#include "Ground.h"
#include "BoxOutline.h"

void
Scene4::init() {
	Scene::init();

	// cargar la textura
	Texture* ground = new Texture();
	ground->load("../assets/images/baldosaC.png");
	gTextures.push_back(ground);

	// variables
	float groundW = 200;
	float groundH = 200;

	//gObjects.push_back(new Ground(groundW, groundH, ground));
	gObjects.push_back(new BoxOutline(groundW));
}