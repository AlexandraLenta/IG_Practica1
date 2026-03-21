#include "IG1App.h"

#include <iostream>
#include "Image.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace std;

// static single instance (singleton pattern)
IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

// Print OpenGL errors and warnings
void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                   GLsizei length, const GLchar* message, const void* userParam)
{
	const char* prefix = (type == GL_DEBUG_TYPE_ERROR)
		? "\x1b[31m[ERROR]\x1b[0m "
		: "\x1b[33m[WARNING]\x1b[0m ";
	cout << prefix << message << endl;
}

void
IG1App::close()
{
	cout << "Closing GLFW...\n";
	glfwSetWindowShouldClose(mWindow, true); // stops main loop
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWindow == 0) // if not intilialized
		init();

	mNextUpdate = glfwGetTime() + FRAME_DURATION;
	double currentTime = glfwGetTime();

	// IG1App main loop
	while (!glfwWindowShouldClose(mWindow)) {

		currentTime = glfwGetTime();

		// if update enabled and its time to update again
		if (mUpdateEnabled && currentTime >= mNextUpdate) {
			mScenes[mCurrentScene]->update();
			mNeedsRedisplay = true;
			mNextUpdate += FRAME_DURATION;
		}
		// Redisplay the window if needed
		if (mNeedsRedisplay) {
			display();
			mNeedsRedisplay = false;
		}

		if (mUpdateEnabled) {
			double timeout = mNextUpdate - glfwGetTime();
			if (timeout < 0.0) timeout = 0.0;
			glfwWaitEventsTimeout(timeout);
		}
		else {
			// Stop and wait for new events
			glfwWaitEvents();
		}

	}

	destroy();
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH);
	mCamera = new Camera(mViewPort);
	//mScenes.push_back(new Scene);
	//mScenes.push_back(new Scene1);
	//mScenes.push_back(new Scene2);
	//mScenes.push_back(new Scene3);
	mScenes.push_back(new Scene4);

	mCamera->set2D();
	for (Scene* scene : mScenes) scene->init();
	mScenes[mCurrentScene]->load();
}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting GLFW...\n";
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // enable on macOS
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Create window with its associated OpenGL context, return window's pointer
	mWindow = glfwCreateWindow(mWinW, mWinH, "IG1App", nullptr, nullptr);

	if (mWindow == nullptr) {
		glfwTerminate();
		throw std::logic_error("cannot create GLFW window");
	}

	glfwMakeContextCurrent(mWindow);

	// Initialize OpenGL extension library
	if (GLenum err = glewInit(); err != GLEW_OK) {
		glfwTerminate();
		throw std::logic_error("Error while loading extensions: "s +
		                       reinterpret_cast<const char*>(glewGetErrorString(err)));
	}

	// Callback registration
	glfwSetWindowSizeCallback(mWindow, s_resize);
	glfwSetCharCallback(mWindow, s_key);
	glfwSetKeyCallback(mWindow, s_specialkey);
	glfwSetWindowRefreshCallback(mWindow, s_display);

	// mouse callbacks
	glfwSetMouseButtonCallback(mWindow, s_mouse);
	glfwSetCursorPosCallback(mWindow, s_motion);
	glfwSetScrollCallback(mWindow, s_mouseWheel);

	// Error message callback (all messages)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0u, 0, GL_TRUE);
	glDebugMessageCallback(debugCallback, nullptr);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::destroy()
{ // release memory and resources
	for (Scene* scene : mScenes)
		delete scene;
	mScenes.clear();

	delete mCamera;
	mCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;

	glfwTerminate();
}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	//mScenes[mCurrentScene]->render(*mCamera); // uploads the viewport and camera to the GPU

	//glfwSwapBuffers(mWindow); // swaps the front and back buffer

	if (!m2Vistas) {
		//solo 1 vist
		mViewPort->setPos(0, 0);
		mViewPort->setSize(mWinW, mWinH);

		mCamera->upload();
		mScenes[mCurrentScene]->render(*mCamera);
	}
	else {
		display2V();
	}
	glfwSwapBuffers(mWindow);
}

void
IG1App::display2V() const {
	// camera auxiliar
	Camera auxCam = *mCamera; // copia camera

	Viewport auxVP = *mViewPort; // copia viewport

	mViewPort->setSize(mWinW / 2, mWinH); // mismo height, width dividido en dos

	auxCam.setSize(mViewPort->width(), mViewPort->height());

	// izquierda, vista 3d
	mViewPort->setPos(0, 0);
	
	auxCam.set3D();
	
	mScenes[mCurrentScene]->render(auxCam); // renderizamos

	// derecha, cenital
	mViewPort->setPos(mWinW / 2, 0);

	auxCam.setCenital();

	mScenes[mCurrentScene]->render(auxCam);

	*mViewPort = auxVP; // restaurar viewport
}

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}

void
IG1App::key(unsigned int key)
{
	bool need_redisplay = true;

	switch (key) {
		case '+':
			mCamera->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case '-':
			mCamera->setScale(-0.01); // zoom out (decreases the scale)
			break;
		case 'l':
			mCamera->set3D();
			break;
		case 'o':
			mCamera->set2D();
			break;
		case 'u':
			mScenes[mCurrentScene]->update();
			break;
		case 'U':
			mUpdateEnabled = !mUpdateEnabled;
			if (mUpdateEnabled)
			{
				cout << "Enable continuous update. \n";
				mNextUpdate = glfwGetTime() + FRAME_DURATION;
			}
			else {
				cout << "Disable continuous update.\n";
			}
				break;
		case 'F':
			saveImage();
			cout << "Save image\n";
			break;
		case 'w':
			mCamera->moveUD(1);
			break;
		case 's':
			mCamera->moveUD(-1);
			break;
		case 'W':
			mCamera->moveFB(1);
			break;
		case 'S':
			mCamera->moveFB(-1);
			break;
		case 'a':
			mCamera->moveLR(1);
			break;
		case 'd':
			mCamera->moveLR(-1);
			break;
		case 'p':
			mCamera->changePrj();
			break;
		case 'k':
			m2Vistas = !m2Vistas;
			break;
		case 'O': // TESTING
			mCamera->orbit(1, 1);
			break;
		default:
			if (key >= '0' && key <= '9') {
				if (changeScene(key - '0')) break;
				cout << "[NOTE] There is no scene " << char(key) << ".\n";
			}
			need_redisplay = false;
			break;
	} // switch
	
	mNeedsRedisplay = need_redisplay;
}

void
IG1App::specialkey(int key, int scancode, int action, int mods)
{
	// Only interested in press events
	if (action == GLFW_RELEASE)
		return;

	bool need_redisplay = true;

	// Handle keyboard input
	// (key reference: https://www.glfw.org/docs/3.4/group__keys.html)
	switch (key) {
		case GLFW_KEY_ESCAPE:                     // Escape key
			glfwSetWindowShouldClose(mWindow, true); // stops main loop
			break;
		case GLFW_KEY_RIGHT:
			if (mods == GLFW_MOD_CONTROL)
				mCamera->rollReal(-1); // rolls towards the right
			else
				mCamera->yawReal(-1); // looks to the right
			break;
		case GLFW_KEY_LEFT:
			if (mods == GLFW_MOD_CONTROL)
				mCamera->rollReal(1); // rolls towards the left
			else
				mCamera->yawReal(1); // looks to the left
			break;
		case GLFW_KEY_UP:
			mCamera->pitchReal(1); // pitches upwards
			break;
		case GLFW_KEY_DOWN:
			mCamera->pitchReal(-1); // pitches downwards
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

bool
IG1App::changeScene(size_t sceneNr)
{
	// Check whether the scene exists
	if (sceneNr >= mScenes.size())
		return false;

	// Change only if a different scene
	if (sceneNr != mCurrentScene) {
		mScenes[mCurrentScene]->unload();
		mCurrentScene = sceneNr;
		mScenes[mCurrentScene]->load();
	}

	return true;
}

void
IG1App::saveImage() {
	Image* img = new Image();
	img->saveImg();
	delete img;
	img = nullptr;
}

void 
IG1App::s_mouse(GLFWwindow* win, int button,
	int action, int mods) {
	s_ig1app.mouse(button, action, mods);
}

void 
IG1App::s_motion(GLFWwindow* win,
	double x, double y) {
	s_ig1app.motion(x, y);
}

void
IG1App::s_mouseWheel(GLFWwindow* win,
	double dx, double dy) {
	s_ig1app.mouseWheel(dx, dy);
}

void 
IG1App::mouse(int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		mMouseButt = button;
	}
	else {
		mMouseButt = -1;
	}

	double xpos, ypos;
	glfwGetCursorPos(s_ig1app.mWindow, &xpos, &ypos);

	// DUDA: es necesario hacer el paso de y de ventana a y del puerto de vista? 
	// funciona mal si lo hacemos

	mMouseCoord = { xpos, ypos };
}

void 
IG1App::motion(double x, double y) {
	glm::dvec2 mp = mMouseCoord - glm::dvec2{ x, y }; // how much we've moved

	mMouseCoord = glm::dvec2(x, y); // new position

	if (mMouseButt == GLFW_MOUSE_BUTTON_LEFT) { // if its the left button
		mCamera->orbit(mp.x * 0.05, -mp.y);
	}
	else if (mMouseButt == GLFW_MOUSE_BUTTON_RIGHT) { // if its the right button
		mCamera->moveLR(-mp.x);
		mCamera->moveUD(mp.y);

	}
	mNeedsRedisplay = true;

	// TODO: vector de objetos transparentes en scene4
}

void 
IG1App::mouseWheel(double dx, double dy) {
	int key = glfwGetKey(s_ig1app.mWindow, GLFW_KEY_LEFT_CONTROL); // if control is pressed 
	
	// DUDA: asi se verifica si esta pressed el modifier?

	if (key == GLFW_PRESS) {
		mCamera->setScale(dy * 0.05);
	}
	else {
		mCamera->moveFB(dy);
	}

	mNeedsRedisplay = true;
}

