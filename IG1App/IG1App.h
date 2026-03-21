#ifndef _H_IG1App_H_
#define _H_IG1App_H_

#include <GL/glew.h>     // OpenGL Extension Wrangler
#include <GLFW/glfw3.h>  // OpenGL Library
#include <glm/glm.hpp>   // OpenGL Mathematics

#include "Camera.h"
#include "Scene.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Viewport.h"

class IG1App
{
public:
	// static single instance (singleton pattern)
	static IG1App s_ig1app;

	IG1App(IG1App const& J) = delete;         // no copy constructor
	void operator=(IG1App const& J) = delete; // no copy assignment

	// Viewport position and size
	Viewport const& viewPort();
	// Camera position, view volume and projection
	Camera const& camera();
	// Graphics objects of the scene
	Scene const& scene();

	// Change to the given scene
	bool changeScene(size_t sceneNr);

	void run();   // the main event processing loop
	void close(); // the application

	void saveImage();
	bool m2Vistas = false;

protected:
	IG1App() = default;
	~IG1App() { close(); };

	void init();
	void iniWinOpenGL();
	void destroy();

	void display() const;                      // the scene
	void display2V() const;
	void resize(int newWidth, int newHeight);  // the viewport (without changing the scale)
	void key(unsigned int codepoint);          // keypress event
	void specialkey(int key, int scancode, int action, int mods); // special keypress event

	// static callbacks
	static void s_display(GLFWwindow*) { s_ig1app.display(); };
	static void s_resize(GLFWwindow*, int newWidth, int newHeight) { s_ig1app.resize(newWidth, newHeight); };
	static void s_key(GLFWwindow* win, unsigned int codepoint) { s_ig1app.key(codepoint); };
	static void s_specialkey(GLFWwindow* win, int key, int scancode, int action, int mods) { s_ig1app.specialkey(key, scancode, action, mods); };

	static void s_mouse(GLFWwindow* win, int button,
		int action, int mods);
	static void s_motion(GLFWwindow* win,
		double x, double y);
	static void s_mouseWheel(GLFWwindow* win,
		double dx, double dy);


	// Viewport position and size
	Viewport* mViewPort = nullptr;
	// Camera position, view volume and projection
	Camera* mCamera = nullptr;
	// Graphics objects are in the scenes
	std::vector<Scene*> mScenes;
	size_t mCurrentScene = 0;

	bool mNeedsRedisplay = true;   // main event processing loop
	GLFWwindow* mWindow = nullptr; // window's handle
	int mWinW = 800;               // window's width
	int mWinH = 600;               // window's height

	// Apartado 14
	double const FRAME_DURATION = 1.0 / 20.0;
	bool mUpdateEnabled = false;
	double mNextUpdate = 0.0;

	//apartado 50
	glm::dvec2 mMouseCoord;// Guarda coordenadas x y del raton
	int mMouseButt = -1; // Guarda el boton del raton que pulsa

	void mouse(int button, int state, int mods);
	void motion(double x, double y);
	void mouseWheel(double dx, double dy);

	void initDisplay2V();
};

inline Viewport const&
IG1App::viewPort()
{
	return *mViewPort;
}

inline Camera const&
IG1App::camera()
{
	return *mCamera;
}

inline Scene const&
IG1App::scene()
{
	return *mScenes[mCurrentScene];
}

#endif //_H_IG1App_H_
