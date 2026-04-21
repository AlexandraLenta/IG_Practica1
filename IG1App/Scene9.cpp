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
    GLdouble eyeOffset = headR * 0.3;
    GLdouble sphereRes = 40; // numero de paralelos y meridianos
    GLfloat eyeRotOffset = 25.0f; // grados
    
    glm::vec4 snowmanColor = { 0.95f, 0.95f, 0.95f, 1 }; // gris
    glm::vec4 noseColor = { 1.0f, 0.4f, 0.0f, 1.0f }; // naranja
    glm::vec4 brimColor = { 0.0f, 1.0f, 1.0f, 1.0f }; // turquesa
    glm::vec4 eyeColor = { 0.0f, 0.5f, 0.5f, 1.0f }; // verde-azulado
    glm::vec4 hatColor = { 0.0f, 0.0f, 1.0f, 1.0f }; // azul
    glm::vec4 topColor = { 1.0f, 0.0f, 0.0f, 1.0f }; // rojo
  

    // cuerpo: eesfera inferior
    Sphere* lower = new Sphere(bodyR, sphereRes, sphereRes, snowmanColor);
    snowMan->addEntity(lower);

    //cabeza : esfera superior
    Sphere* upper = new Sphere(headR, sphereRes, sphereRes, snowmanColor);
    glm::mat4 headMat = glm::translate(glm::mat4(1.0f), { 0, bodyR + headR * 0.8, 0 });
    upper->setModelMat(headMat);
    snowMan->addEntity(upper);

    // nariz
    Cone* nose = new Cone(headR * 0.6, 0.0, headR * 0.15, 10, 20, noseColor);
    glm::mat4 noseRot = glm::rotate(glm::mat4(1.0f),glm::radians(-90.0f), glm::vec3(1, 0, 0));
    glm::mat4 nosePos = glm::translate(glm::mat4(1.0f),glm::vec3(0, bodyR + headR * 0.8, headR));
    nose->setModelMat(nosePos * noseRot);
    snowMan->addEntity(nose);

    //ojos

    Cone* eyeL = new Cone(headR * 0.2, 0.0,15,10 ,10, eyeColor);
    Cone* eyeR = new Cone(headR * 0.3, 0.0, 15, 10, 10, eyeColor);

    glm::mat4 eyeRot = glm::rotate(glm::mat4(1.0f),glm::radians(-90.0f), glm::vec3(1, 0, 0));
    glm::mat4 eyeLRot = glm::rotate(glm::mat4(1.0f), glm::radians(-eyeRotOffset), glm::vec3(0, 1, 0));
    glm::mat4 eyeRRot = glm::rotate(glm::mat4(1.0f), glm::radians(eyeRotOffset), glm::vec3(0, 1, 0));

    glm::mat4 eyeLPos = glm::translate(glm::mat4(1.0f),glm::vec3(-eyeOffset, bodyR + headR, headR));
    glm::mat4 eyeRPos = glm::translate(glm::mat4(1.0f),glm::vec3(eyeOffset, bodyR + headR, headR));

    eyeR->setModelMat(eyeRPos * eyeRot);
    eyeL->setModelMat(eyeLPos * eyeRot);


    snowMan->addEntity(eyeL);
    snowMan->addEntity(eyeR);

    CompoundEntity* hat = new CompoundEntity();

    // gorro
    Disk* brim = new Disk(bodyR, headR * 0.6, sphereRes, sphereRes, brimColor);
    brim->setModelMat(glm::translate(glm::mat4(1.0f), { 0, bodyR + headR * 1.6, 0 }));
    hat->addEntity(brim);

    // cuerpo del gorro
    Cone* hatBody = new Cone(headR-15, headR * 0.85, headR * 0.85,20, sphereRes, hatColor);
    hatBody->setModelMat(glm::translate(glm::mat4(1.0f),glm::vec3(0, bodyR + headR * 2.0, 0)));
    hat->addEntity(hatBody);

    // tapa del gorro
    Disk* top = new Disk(headR * 0.85, 0.0, sphereRes, sphereRes, topColor);
    top->setModelMat(glm::translate(glm::mat4(1.0f),glm::vec3(0, bodyR + headR * 2.39, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1, 0, 0)));

    hat->addEntity(top);

    snowMan->addEntity(hat);

    gObjects.push_back(snowMan);
}