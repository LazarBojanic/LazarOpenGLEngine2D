#pragma once

#include "GLData.hpp"
#include "GameObject.hpp"
#include "ResourceManager.hpp"

class Renderer {
private:
	Renderer();
	~Renderer();
	static Renderer* instance;

public:
	static Renderer* getInstance();
	void draw(GameObject& gameObject, glm::vec2 position, glm::vec2 size, float rotationRadians);
	void colorBackground(glm::vec4 color);
};