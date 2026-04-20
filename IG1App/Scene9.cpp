#include "Scene9.h"
#include "Cone.h"
#include "Sphere.h"
#include "CompoundEntity.h"
#include "Disk.h"
void Scene9::init()
{
    Scene::init();

    CompoundEntity* snowMan = new CompoundEntity();

    GLdouble bodyR = 100.0;
    GLdouble headR = bodyR * 0.7;

    // cuerpo
    Sphere* lower = new Sphere(bodyR, 40, 40, { 0.95f, 0.95f, 0.95f, 1 });
    snowMan->addEntity(lower);

    //cabeza
    Sphere* upper = new Sphere(headR, 40, 40, { 0.95f, 0.95f, 0.95f, 1 });
    glm::mat4 headMat = glm::translate(glm::mat4(1.0f), { 0, bodyR + headR * 0.8, 0 });
    upper->setModelMat(headMat);
    snowMan->addEntity(upper);

    // nariz
    Cone* nose = new Cone(headR * 0.6, 0.0, headR * 0.15, 10, 20,{ 1.0f, 0.4f, 0.0f, 1.0f });
    glm::mat4 noseRot = glm::rotate(glm::mat4(1.0f),glm::radians(-90.0f), glm::vec3(1, 0, 0));
    glm::mat4 nosePos = glm::translate(glm::mat4(1.0f),glm::vec3(0, bodyR + headR * 0.8, headR));
    nose->setModelMat(nosePos * noseRot);
    snowMan->addEntity(nose);

    GLdouble eyeOffset = headR * 0.25;
    glm::vec4 eyeColor = { 0.0f, 0.5f, 0.5f, 1.0f };

    Cone* eyeL = new Cone(headR * 0.2, 0.0,10,10 ,10, eyeColor);
    Cone* eyeR = new Cone(headR * 0.3, 0.0, 10, 10, 10, eyeColor);

    glm::mat4 eyeRot = glm::rotate(glm::mat4(1.0f),glm::radians(-90.0f), glm::vec3(1, 0, 0));

    glm::mat4 eyeLPos = glm::translate(glm::mat4(1.0f),glm::vec3(-eyeOffset, bodyR + headR, headR));
    glm::mat4 eyeRPos = glm::translate(glm::mat4(1.0f),glm::vec3(eyeOffset, bodyR + headR, headR));

    eyeL->setModelMat(eyeLPos * eyeRot);
    eyeR->setModelMat(eyeRPos * eyeRot);


    snowMan->addEntity(eyeL);
    snowMan->addEntity(eyeR);

    CompoundEntity* hat = new CompoundEntity();

    // gorro
    Disk* brim = new Disk(bodyR, headR * 0.6, 40, 40,{ 0.0f, 1.0f, 1.0f, 1.0f });
    brim->setModelMat(glm::translate(glm::mat4(1.0f), { 0, bodyR + headR * 1.6, 0 }));
    hat->addEntity(brim);

    // cuerpo del gorro
    Cone* hatBody = new Cone(headR, headR * 0.6, headR * 0.6,20, 40,{ 0.0f, 0.0f, 1.0f, 1.0f });
    hatBody->setModelMat(glm::translate(glm::mat4(1.0f),glm::vec3(0, bodyR + headR * 2.0, 0)));
    hat->addEntity(hatBody);

    // tapa del gorro
    Disk* top = new Disk(headR * 0.6, 0.0, 40, 40,{ 1.0f, 0.0f, 0.0f, 1.0f });
    top->setModelMat(glm::translate(glm::mat4(1.0f),glm::vec3(0, bodyR + headR * 2.5, 0)));

    hat->addEntity(top);

    snowMan->addEntity(hat);

    gObjects.push_back(snowMan);
}