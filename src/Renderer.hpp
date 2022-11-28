#pragma once

#include "GLData.hpp"
#include "GameObject.hpp"

class Renderer {
private:
	Renderer();
	~Renderer();
	static Renderer* instance;

public:
	static Renderer* getInstance();
	void draw(GameObject& gameObject);
	void colorBackground(glm::vec4 color);
};