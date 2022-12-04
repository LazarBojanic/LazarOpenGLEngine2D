#pragma once

#include "GLData.hpp"

class Entity {
public:
	std::string name;
	glm::vec2 position;
	glm::vec2 size;
	float rotation;
	bool isHit;
	Entity(std::string name, glm::vec2 position, glm::vec2 size, float rotation, bool isHit);
	~Entity();
};