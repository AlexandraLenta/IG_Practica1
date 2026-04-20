#include "CompoundEntity.h"

CompoundEntity::~CompoundEntity() {
	for (auto& e : gObjects) {
		delete e;
	}
}

void CompoundEntity::addEntity(Abs_Entity* ae) {
	gObjects.push_back(ae);
}

void CompoundEntity::render(const glm::mat4& modelViewMat) const {
	for (auto& e : gObjects)
		e->render(modelViewMat);
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