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
			if (m2Vistas) {
				mScenes[0]->update();
				mScenes[1]->update();
			}
			else
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

	mScenes.push_back(new Scene10);
	//mScenes.push_back(new Scene);
	mScenes.push_back(new Scene1);
	mScenes.push_back(new Scene2);
	mScenes.push_back(new Scene3);
	mScenes.push_back(new Scene4);
	mScenes.push_back(new Scene5);
	mScenes.push_back(new Scene6);
	mScenes.push_back(new Scene7);
	mScenes.push_back(new Scene8);
	mScenes.push_back(new Scene9);


	mCamera->set2D();
	for (Scene* scene : mScenes) scene->init();
	mScenes[mCurrentScene]->load();
	mScenes[mCurrentScene]->setGL();

	mMouseButt = -1; //ningun mouse culo activo
	mActiveViewport = -1; //ningun viewport activo
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

	delete mCameraLeft;
	delete mCameraRight;
	mCameraLeft = nullptr;
	mCameraRight = nullptr;


	delete mViewportLeft;
	delete mViewportRight;
	mViewportLeft = nullptr;
	mViewportRight = nullptr;

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

	if (!m2Vistas) {
		// one view
		mViewPort->setPos(0, 0);
		mViewPort->setSize(mWinW, mWinH);

		mCamera->upload();
		mScenes[mCurrentScene]->render(*mCamera);
	}
	else { // two views
		display2V();
	}

	glfwSwapBuffers(mWindow);
}

void
IG1App::display2V() const {

	//vista izq
	mViewportLeft->setPos(0, 0);
	mViewportLeft->setSize(mWinW / 2, mWinH);
	mViewportLeft->upload();

	mCameraLeft->setSize(mWinW / 2, mWinH);
	mCameraLeft->upload();
	mScenes[0]->render(*mCameraLeft);

	// derecha
	mViewportRight->setPos(mWinW / 2, 0);
	mViewportRight->setSize(mWinW / 2, mWinH);
	mViewportRight->upload();

	mCameraRight->setSize(mWinW / 2, mWinH);
	mCameraRight->upload();
	mScenes[1]->render(*mCameraRight);
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

	Camera* cam = mCamera;
	if (m2Vistas) {
		if (mActiveViewport == 0) {
			cam = mCameraLeft;
		}
		else {
			cam = mCameraRight;
		}
	}

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
			if (m2Vistas)
				mScenes[mActiveViewport]->update();
			else
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
			cam->moveUD(1);
			break;
		case 's':
			cam->moveUD(-1);
			break;
		case 'W':
			cam->moveFB(1);
			break;
		case 'S':
			cam->moveFB(-1);
			break;
		case 'a':
			cam->moveLR(-1);
			break;
		case 'd':
			cam->moveLR(1);
			break;
		case 'p':
			cam->changePrj();
			break;
		case 'k':
			m2Vistas = !m2Vistas;
			initDisplay2V();
			break;
		case 'N':
			ColorMaterialEntity::toggleShowNormals();
			break;
		case 'f':
			mScenes[mCurrentScene]->rotate();
			break;
		case 'g':
			mScenes[mCurrentScene]->orbit();
			break;
		case 'r':
			mScenes[mCurrentScene]->toggleDirLight();
			break;
		case 't':
			mScenes[mCurrentScene]->togglePosLight();
			break;
		case 'y':
			mScenes[mCurrentScene]->toggleSpotLight();
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

	// Seleccionar la cam activa segun el viewport donde esta el cursor
	Camera* cam = mCamera;
	if (m2Vistas) {
		if (mActiveViewport == 0) cam = mCameraLeft;
		else if (mActiveViewport == 1) cam = mCameraRight;
	}
	// Handle keyboard input
	// (key reference: https://www.glfw.org/docs/3.4/group__keys.html)
	switch (key) {
		case GLFW_KEY_ESCAPE:                     // Escape key
			glfwSetWindowShouldClose(mWindow, true); // stops main loop
			break;
		case GLFW_KEY_RIGHT:
			if (mods == GLFW_MOD_CONTROL)
				cam->rollReal(1); // rolls towards the right
			else
				cam->yawReal(-1); // looks to the right
			break;
		case GLFW_KEY_LEFT:
			if (mods == GLFW_MOD_CONTROL)
				cam->rollReal(-1); // rolls towards the left
			else
				cam->yawReal(1); // looks to the left
			break;
		case GLFW_KEY_UP:
			cam->pitchReal(1); // pitches upwards
			break;
		case GLFW_KEY_DOWN:
			cam->pitchReal(-1); // pitches downwards
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
		
		// ponemos el GL de la nueva escena
		mScenes[mCurrentScene]->setGL();
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

	int height;
	glfwGetWindowSize(mWindow, nullptr, &height);
	ypos = height - ypos; // conversion of y from window to y from viewport

	mMouseCoord = { xpos, ypos };
	// Detectar en que viewport esta el cursor
	if (m2Vistas) {
		if (xpos < mWinW / 2) mActiveViewport = 0;
		else mActiveViewport = 1;
	}
}

void 
IG1App::motion(double x, double y) {
	int height;
	glfwGetWindowSize(mWindow, nullptr, &height);
	y = height - y; // conversion of y from window to y from viewport

	glm::dvec2 mp = mMouseCoord - glm::dvec2{ x, y }; // how much we've moved

	mMouseCoord = glm::dvec2(x, y); // new position

	// Seleccionar la cam activa
	Camera* cam = mCamera;
	if (m2Vistas) {
		if (mMouseCoord.x < mWinW / 2) {
			cam = mCameraLeft;
			mActiveViewport = 0;
		}
		else {
			cam = mCameraRight;
			mActiveViewport = 1;
		}
	}

	if (mMouseButt == GLFW_MOUSE_BUTTON_LEFT) { // if its the left button
		cam->orbit(mp.x * 0.05, mp.y);
	}
	else if (mMouseButt == GLFW_MOUSE_BUTTON_RIGHT) { // if its the right button
		cam->moveLR(mp.x);
		cam->moveUD(mp.y);

	}
	mNeedsRedisplay = true;

	// TODO: vector de objetos transparentes en scene4
}

void 
IG1App::mouseWheel(double dx, double dy) {
	Camera* cam = mCamera;
	if (m2Vistas) {
		if (mActiveViewport == 0) cam = mCameraLeft;
		else cam = mCameraRight;
	}

	int ctrlState = glfwGetKey(s_ig1app.mWindow, GLFW_KEY_LEFT_CONTROL); // if control is pressed 

	if (ctrlState == GLFW_PRESS) {
		cam->setScale(dy * 0.05);
	}
	else {
		cam->moveFB(dy);
	}

	mNeedsRedisplay = true;
}

void
IG1App::initDisplay2V() {
	if (m2Vistas) {
		mScenes[1]->load();	
		
		// Crear viewport izq y su cam 
		mViewportLeft = new Viewport(mWinW / 2, mWinH);
		mViewportLeft->setPos(0, 0);
		mCameraLeft = new Camera(mViewportLeft);
		mCameraLeft->set3D();

		// Crear viewport derecho y su cam 
		mViewportRight = new Viewport(mWinW / 2, mWinH);
		mViewportRight->setPos(mWinW / 2, 0);
		mCameraRight = new Camera(mViewportRight);
		mCameraRight->set2D();
	}
	else {
		mScenes[1]->unload();
		delete mViewportLeft;
		delete mViewportRight;
		mViewportLeft = nullptr;
		mViewportRight = nullptr;

		delete mCameraLeft;
		delete mCameraRight;
		mCameraLeft = nullptr;
		mCameraRight = nullptr;
	}
}
