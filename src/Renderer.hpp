#pragma once

#include "Util.hpp"
#include "ResourceManager.hpp"
#include "GameObjectManager.hpp"

class Renderer {
private:
	Renderer();
	~Renderer();
	static Renderer* instance;

public:
	static Renderer* getInstance();
	void drawAll(bool scaled);
	void draw(GameObject& gameObject, bool scaled);
	void drawAllUntextured(bool scaled);
	void drawUntextured(GameObject& gameObject, bool scaled);
	void colorBackground(glm::vec4 color);
};