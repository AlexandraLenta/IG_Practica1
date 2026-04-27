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

	virtual void rotate() {};
	virtual void orbit() {};

	void uploadLights(const Camera& cam) const;

protected:
	void destroy();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> transparentObj; // Transparent/Translucent entities of the scene
	TextureLoader* texLoader;

	std::vector<Light*> gLights;
};

#endif //_H_Scene_H_
