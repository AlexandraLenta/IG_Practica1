#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Viewport.h"

class Camera
{
public:
	explicit Camera(Viewport* vp);
	~Camera() = default;

	// viewPort
	Viewport const& viewPort() const { return *mViewPort; };

	// view matrix
	glm::mat4 const& viewMat() const { return mViewMat; };

	void set2D();
	void set3D();

	void pitch(GLfloat a); // rotates a degrees on the X axis
	void yaw(GLfloat a);   // rotates a degrees on the Y axis
	void roll(GLfloat a);  // rotates a degrees on the Z axis

	// projection matrix
	glm::mat4 const& projMat() const { return mProjMat; };

	// sets scene visible area size
	void setSize(GLdouble xw, GLdouble yh);
	// updates the scale factor
	void setScale(GLdouble s);

	// transfers its viewport, the view matrix and projection matrix to the GPU
	void upload() const;

	// move left right
	void moveLR(GLfloat cs);

	// move forward back
	void moveFB(GLfloat cs);

	// move up down
	void moveUD(GLfloat cs);

	// change to perspective projection
	void changePrj();

protected:
	glm::vec3 mEye = {0.0, 0.0, 500.0}; // camera's position
	glm::vec3 mLook = {0.0, 0.0, 0.0};  // target's position
	glm::vec3 mUp = {0.0, 1.0, 0.0};    // the up vector

	glm::mat4 mViewMat;   // view matrix = inverse of modeling matrix
	void uploadVM() const; // transfers viewMat to the GPU

	glm::mat4 mProjMat;   // projection matrix
	void uploadPM() const; // transfers projMat to the GPU

	GLfloat xRight, xLeft, yTop, yBot;     // size of scene visible area
	GLfloat mNearVal = 1, mFarVal = 10000; // view volume
	GLfloat mScaleFact = 1;                // scale factor
	bool bOrto = true;                      // orthogonal or perspective projection

	Viewport* mViewPort; // the viewport

	glm::vec3 mRight;
	glm::vec3 mUpward;
	glm::vec3 mFront;

	void setVM();
	void setPM();

	void setAxes();

private:
	glm::vec4 row(glm::mat4 mat, int index) {
		return glm::vec4(
			mat[0][index],
			mat[1][index],
			mat[2][index],
			mat[3][index]
		);
	}
};

#endif //_H_Camera_H_
