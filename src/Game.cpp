#include "Game.hpp"

Game* Game::instance;

Game::Game(unsigned int width, unsigned int height) {
	this->gameState = GAME_ACTIVE;
	this->width = width;
	this->height = height;
	this->keys = new bool[1024];
}

Game::~Game() {
	delete this->keys;
}

Game* Game::getInstance(unsigned int width, unsigned int height) {
	if (!instance) {
		instance = new Game(width, height);
	}
	return instance;
}
Game* Game::getInstance() {
	if (!instance) {
		instance = new Game(0, 0);
	}
	return instance;
}

void Game::init() {
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	Shader* triangleShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\triangleVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\triangleFragmentShader.glsl", "triangleShader");
	Texture2D* triangleTexture = ResourceManager::getInstance()->addTexture2D("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\textures\\awesomeface.png", true, "triangleTexture");
	Triangle* triangle = new Triangle();
	/*Mesh* triangleMesh = new Mesh(
		triangle->getData(),
		24 * sizeof(float),
		triangle->getIndices(),
		3 * sizeof(unsigned int),
		"triangleMesh",
		0, 3, 1, 3, 2, 2, *triangleTexture, 0
		);*/
	Mesh* triangleMesh = new Mesh(*triangle, "triangleMesh", 0, 3, 1, 3, 2, 2);
	GameObject* triangleGameObject = new GameObject("triangleGameObject", *triangleMesh, *triangleShader, *triangleTexture);
	GameObjectManager::getInstance()->addGameObject(*triangleGameObject);
	
}

void Game::processInput(float dt) {
	if (this->keys[GLFW_KEY_UP]) {

	}
	if (this->keys[GLFW_KEY_DOWN]) {

	}
}

void Game::update(float dt) {
}

void Game::render(float dt) {
	Renderer::getInstance()->colorBackground(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

	GameObject* triangleGameObject = GameObjectManager::getInstance()->getGameObjectByName("triangleGameObject");
	Renderer::getInstance()->draw(*triangleGameObject);
}
void Game::clear() {

}
