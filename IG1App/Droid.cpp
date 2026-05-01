#include "Droid.h"
#include "SphereWithTexture.h"
#include "Disk.h"
#include "Cone.h"
#include "Scene.h"
#include <iostream>

Droid::Droid(GLdouble radius, Texture* bodyTex) {
	// body
	addEntity(new SphereWithTexture(radius, 40, 40, bodyTex));

	createHead(radius);
	createLight(radius);
}

Droid::~Droid() {
	delete mSpotLight;
}

void 
Droid::toggleLight() {
	mSpotLight->setEnabled(!mSpotLight->enabled());
}

void
Droid::createHead(GLfloat radius) {

	CompoundEntity* headEntity = new CompoundEntity();

	// variables
	GLdouble headHeight = radius * 0.5f;
	GLdouble eyePos = headHeight * 0.5f;
	GLdouble eyeRadius = headHeight * 0.25f;
	glm::vec4 headColor = { 1.0, 1.0, 0.0, 1.0 };
	int rings = 40;

	//head
	Cone* head = new Cone(headHeight,radius,headHeight,rings,rings, headColor);
	head->setModelMat(glm::translate(glm::mat4(1.0f),glm::vec3(0, radius + headHeight * 0.5f, 0))); // mover encima del cuerpo
	headEntity->addEntity(head);

	// disks
	Disk* upperCover = new Disk(0, headHeight, rings, rings, headColor);
	Disk* lowerCover = new Disk(0, radius, rings, rings, headColor);

	upperCover->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0, radius + headHeight, 0)));
	headEntity->addEntity(upperCover);

	glm::mat4 lowerRot = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0, 0, 1));
	glm::mat4 lowerPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, radius, 0));
	lowerCover->setModelMat(lowerPos * lowerRot);

	headEntity->addEntity(lowerCover);

	//Ojos
	Cone* eyeL = new Cone(headHeight, eyeRadius, eyeRadius, rings / 2, rings / 2, { 0.0, 0.8, 0.0, 1.0 });
	Cone* eyeR = new Cone(headHeight, eyeRadius, eyeRadius, rings / 2, rings / 2, { 0.0, 0.8, 0.0, 1.0 });

	glm::mat4 eyeRot = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(1, 0, 0)); // rotar alrededor de x 90 grados | -> ---
	glm::mat4 leftPos = glm::translate(glm::mat4(1.0f), glm::vec3(eyeRadius, radius + headHeight * 0.5f, radius)); // mover los ojos
	glm::mat4 rightPos = glm::translate(glm::mat4(1.0f), glm::vec3(-eyeRadius, radius + headHeight * 0.5f, radius));

	eyeL->setModelMat(leftPos * eyeRot); // primero rotamos, luego movemos
	eyeR->setModelMat(rightPos * eyeRot);

	headEntity->addEntity(eyeL);
	headEntity->addEntity(eyeR);

	addEntity(headEntity);
}

void
Droid::createLight(GLfloat radius) {
	// Light
	mSpotLight = new SpotLight(glm::vec3(0, radius, 0), 1);
	mSpotLight->setAmb({ 0.25, 0.25, 0.25 });
	mSpotLight->setDiff({ 0.6, 0.6, 0.6 });
	mSpotLight->setSpec({ 0.0, 0.2, 0.0 });
	mSpotLight->setDirection(glm::vec3(0, -1, 0));
	mSpotLight->setEnabled(false);
}

void Droid::render(const glm::mat4& modelViewMat) const
{
	CompoundEntity::render(modelViewMat);
	Shader* sh = Shader::get("light");

	sh->use();

	mSpotLight->upload(*sh, modelViewMat * mModelMat);
}