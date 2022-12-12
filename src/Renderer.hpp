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
	void draw(GameObject& gameObject, bool scaled);
	void drawUntextured(GameObject& gameObject, bool scaled);
	void colorBackground(glm::vec4 color);
};