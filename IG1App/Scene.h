#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "TextureLoader.h"
#include "Light.h"

#include <vector>

class Scene
{
public:
	enum class LightType {
		DIR_LIGHT,
		POS_LIGHT,
		SPOT_LIGHT
	};

	Scene() = default;
	virtual ~Scene();

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init();

	virtual void render(Camera const& cam) const;
	virtual void update();

	// load or unload scene data into the GPU
	virtual void load();
	virtual void unload();

	virtual void setGL();

	virtual void uploadLights(const Camera& cam) const;
	void toggleLight(LightType lightType, int id);
	void toggleLight(std::string lightID);

	virtual void handleKey(unsigned int key) {}

protected:
	void destroy();
	void resetGL();

	// metodo que busca la luz del tipo dado con el id dado
	Light* findLight(std::string lightID);

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> transparentObj; // Transparent/Translucent entities of the scene
	TextureLoader* texLoader;

	std::vector<Light*> gLights;
};

#endif //_H_Scene_H_
