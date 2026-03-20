#include "Shader.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


using namespace glm;

Camera::Camera(Viewport* vp)
  : mViewMat(1.0)
  , mProjMat(1.0)
  , xRight(vp->width() / 2.0)
  , xLeft(-xRight)
  , yTop(vp->height() / 2.0)
  , yBot(-yTop)
  , mViewPort(vp)
{
	setPM();
}

void
Camera::uploadVM() const
{
	Shader::setUniform4All("modelView", mViewMat);
}

void
Camera::setVM()
{
	mViewMat = lookAt(mEye, mLook, mUp); // glm::lookAt defines the view matrix
	setAxes();
}

void
Camera::set2D()
{
	mEye = {0, 0, 500};
	mLook = {0, 0, 0};
	mUp = {0, 1, 0};
	mRadio = mEye.z;
	mAng = 180;
	setVM();
}

void
Camera::set3D()
{
	mEye = {500, 500, 500};
	mLook = {0, 10, 0};
	mUp = {0, 1, 0};
	mRadio = glm::distance(glm::vec3(mEye.x, 0, mEye.z),glm::vec3(mLook.x, 0, mLook.z));
    mAng = -glm::degrees(atan2(mEye.z - mLook.z,mEye.x - mLook.x));
	setVM();
}

void
Camera::pitch(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(1.0, 0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes(); 
}

void
Camera::yaw(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(0, 1.0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes();
}

void
Camera::roll(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(0, 0, 1.0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes();
}

void
Camera::setSize(GLdouble xw, GLdouble yh)
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}

void
Camera::setScale(GLdouble s)
{
	mScaleFact -= s;
	if (mScaleFact < 0)
		mScaleFact = 0.01;
	setPM();
}

void
Camera::setPM()
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft * mScaleFact,
		                 xRight * mScaleFact,
		                 yBot * mScaleFact,
		                 yTop * mScaleFact,
		                 mNearVal,
		                 mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else { // if not ortho, perspective
		mProjMat = frustum(xLeft * mScaleFact,
			xRight * mScaleFact,
			yBot * mScaleFact, 
			yTop * mScaleFact,
			mNearVal,
			mFarVal);
	}
}

void
Camera::uploadPM() const
{
	Shader::setUniform4All("projection", mProjMat);
}

void
Camera::upload() const
{
	mViewPort->upload();
	uploadVM();
	uploadPM();
}


void
Camera::setAxes() {
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
}

void
Camera::moveLR(GLfloat cs) {
	mEye += mRight * cs;
	mLook += mRight * cs;
	setVM();
	setAxes();
}

void
Camera::moveFB(GLfloat cs) {
	mEye += mFront * cs;
	setVM();
}

void
Camera::moveUD(GLfloat cs) {
	mEye += mUpward * cs;
	mLook += mUpward * cs;
	setVM();
}

void
Camera::changePrj() {
	bOrto = !bOrto;
	setPM();
}

void
Camera::pitchReal(GLfloat cs) {
	//mLook += mUpward * cs;

	glm::mat4 mat = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mRight);

	mFront = glm::vec3(mat * glm::vec4(mFront, 0.0f));
	mUpward = glm::normalize(glm::cross(mRight, mFront));

	mLook = mEye + mFront;

	setVM();
}

void
Camera::yawReal(GLfloat cs) {
	//mLook += mRight * cs;
	glm::mat4 mat = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mUpward);

	mFront = glm::vec3(mat * glm::vec4(mFront, 0.0f));
	mRight = glm::normalize(glm::cross(mFront, mUpward));

	mLook = mEye + mFront;

	setVM();
}

void
Camera::rollReal(GLfloat cs) {
	//mUp += mFront * cs;

	glm::mat4 mat = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mFront);

	mUpward = glm::vec3(mat * glm::vec4(mUpward, 0.0f));
	mRight = glm::normalize(glm::cross(mFront, mUpward));

	mLook = mEye + mFront;
	mUp = mUpward;

	setVM();
}

void
Camera::orbit(GLdouble incAng, GLdouble incY) {
	mAng += incAng;
	mEye.x = mLook.x + cos(glm::radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(glm::radians(mAng)) * mRadio;
	mEye.y += incY;
	setVM();
}

void Camera::setCenital() {
	// camara arriba
	mEye = { 0, 500, 0 };
	mLook = { 0, 0, 0 };	// mira centro
	mUp = { 0, 0, -1 };

	mRadio = glm::distance(glm::vec3(mEye.x, 0, mEye.z),
		glm::vec3(mLook.x, 0, mLook.z));
	mAng = 0.0;

	setVM();
}