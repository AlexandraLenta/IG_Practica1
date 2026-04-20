#include "CompoundEntity.h"

CompoundEntity::~CompoundEntity() {
	for (auto& e : gObjects) {
		delete e;
	}

	gObjects.clear();
}

void CompoundEntity::addEntity(Abs_Entity* ae) {
	gObjects.push_back(ae);
}

void CompoundEntity::render(const glm::mat4& modelViewMat) const {
	// tenemos en cuenta transformaciones sobre la entidad entera
	glm::mat4 aMat = modelViewMat * mModelMat;
	for (auto& e : gObjects)
		e->render(aMat);
}
void CompoundEntity::update() {
	for (auto& e : gObjects)
		e->update();
}
void CompoundEntity::load() {
	for (auto& e : gObjects)
		e->load();
}
void CompoundEntity::unload() {
	for (auto& e : gObjects)
		e->unload();
}