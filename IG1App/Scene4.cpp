#include "Scene4.h"
#include "Ground.h"

void
Scene4::init() {
	Scene::init();

	Texture* ground = new Texture();
	ground->load("../assets/images/baldosaC.png");
	gTexture.push_back(ground);

	gObjects.push_back(new Ground(200, 150, ground));
}