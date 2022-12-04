#include "Entity.hpp"

Entity::Entity(std::string name, glm::vec2 position, glm::vec2 size, float rotation, bool isHit) {
	this->name = name;
	this->position = position;
	this->size = size;
	this->rotation = rotation;
	this->isHit = isHit;
}