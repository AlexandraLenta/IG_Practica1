#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>


using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	DirLight* dir = new DirLight(0);

	dir->setAmb(glm::vec3(0.1f, 0.1f, 0.1f));
	dir->setDiff(glm::vec3(0.5f, 0.5f, 0.5f));
	dir->setSpec(glm::vec3(0.5f, 0.5f, 0.5f));

	dir->setDirection(glm::vec3(-1.0f, -1.0f, -1.0f));
	dir->setEnabled(true);

	gLights.push_back(dir);

	// cargador de texturas
	texLoader = new TextureLoader();
}

Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	for (Light* l : gLights)
		delete l;

	for (Abs_Entity* el : gObjects)
		delete el;

	for (Abs_Entity* el : transparentObj)
		delete el;



	gLights.clear();

	gObjects.clear();
	transparentObj.clear();

	delete texLoader;
}

void
Scene::load()
{
	for (Abs_Entity* obj : gObjects)
		obj->load();

	for (Abs_Entity* obj : transparentObj)
		obj->load();
}

void
Scene::unload()
{
	for (Light* l : gLights)
		l->unload(*Shader::get("simple_light"));
	for (Abs_Entity* obj : gObjects)
		obj->unload();

	for (Abs_Entity* obj : transparentObj)
		obj->unload();


}

void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void
Scene::render(Camera const& cam) const
{

	uploadLights(cam);
	cam.upload();


	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// order transparents
	std::map<float, Abs_Entity*, std::greater<float>> sorted;
	glm::vec3 camPos = cam.getEye();

	for (auto& obj : transparentObj) {
		glm::vec3 pos = glm::vec3(obj->modelMat()[3]);
		float dist = glm::distance(camPos, pos);

		sorted[dist] = obj;
	}

	//render transp
	for (auto& pair : sorted) {
		pair.second->render(cam.viewMat());
	}

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

}

void
Scene::update() {
	for (Abs_Entity* obj : gObjects)
		obj->update();

	for (Abs_Entity* obj : transparentObj)
		obj->update();
}

void 
Scene::uploadLights(const Camera& cam) const
{
	Shader* sh = Shader::get("light");
	sh->use();

	for (auto* l : gLights)
	{
		l->upload(*sh, cam.viewMat());
	}
}

void
Scene::toggleLights()
{
	if (!gLights.empty())
		gLights[0]->setEnabled(!gLights[0]->enabled());
}

void Scene::togglePosLight()
{
	if (gLights.size() > 1)
		gLights[1]->setEnabled(!gLights[1]->enabled());
}

void Scene::toggleSpotLight()
{
	if (gLights.size() > 2)
		gLights[2]->setEnabled(!gLights[2]->enabled());
}
