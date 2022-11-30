#include "Game.hpp"

Game* Game::instance;

Game::Game(unsigned int width, unsigned int height) {
	this->gameState = GAME_ACTIVE;
	this->width = width;
	this->height = height;
	this->keys = new bool[1024];
	initKeys();
}

Game::~Game() {
	delete this->keys;
	delete this->colorsArray;
}

Game* Game::getInstance(unsigned int width, unsigned int height) {
	if (!instance) {
		instance = new Game(width, height);
	}
	return instance;
}
void Game::initKeys() {
	for (int i = 0; i < this->keysSize; i++) {
		this->keys[i] = false;
	}
}
void Game::moveLogo(){

	GameObject* quadGameObject = GameObjectManager::getInstance()->getGameObjectByName("quadGameObject");

	float deltaX = this->logoX - (this->width / 2.0f);
	float deltaY = this->logoY - (25.0f + (this->logoHeight / 2));

	if (deltaX > 0) {
		this->logoX--;
	}
	if (deltaX < 0) {
		this->logoX++;
	}
	if (deltaY > 0) {
		this->logoY--;
	}
	if (deltaY < 0) {
		this->logoY++;
	}

	Renderer::getInstance()->draw(*quadGameObject, glm::vec2(this->logoX, this->logoY), glm::vec2(this->logoWidth, this->logoHeight), 0);

}
Game* Game::getInstance() {
	if (!instance) {
		instance = new Game(0, 0);
	}
	return instance;
}

void Game::init() {
	this->isLogoMove = false;
	glm::mat4 projection = glm::ortho(0.0f, (float)this->width, 0.0f, (float)this->height, -1.0f, 1.0f);
	Shader* triangleShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\triangleVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\triangleFragmentShader.glsl", "triangleShader");
	Shader* quadShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\quadVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\quadFragmentShader.glsl", "quadShader");
	Texture2D* quadTexture = ResourceManager::getInstance()->addTexture2D("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\textures\\dvdLogo.png", true, "quadTexture");
	Triangle* triangle = new Triangle();
	Quad* quad = new Quad();
	
	quadShader->setVector4f("uDvdColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);

	
	


	
	Mesh* triangleMesh = new Mesh(*triangle, "triangleMesh", 0, 3, 1, 3, 2, 2);
	triangleShader->setMatrix4f("uProjection", projection, true);
	GameObject* triangleGameObject = new GameObject("triangleGameObject", *triangleMesh, *triangleShader, *quadTexture);
	GameObjectManager::getInstance()->addGameObject(*triangleGameObject);


	Mesh* quadMesh = new Mesh(*quad, "quadMesh", 0, 3, 1, 3, 2, 2);
	quadShader->setMatrix4f("uProjection", projection, true);
	quadShader->setInt("uTexture", 0, true);
	GameObject* quadGameObject = new GameObject("quadGameObject", *quadMesh, *quadShader, *quadTexture);
	GameObjectManager::getInstance()->addGameObject(*quadGameObject);

	this->logoWidth = 160.0f;
	this->logoHeight = 120.0f;

	this->logoX = 400.0f;
	this->logoY = 450.0f;
	this->logoXSpeed = 3.0f;
	this->logoYSpeed = 3.0f;
}


void Game::processInput(float dt) {
	if (this->keys[GLFW_KEY_UP]) {

	}
	if (this->keys[GLFW_KEY_DOWN]) {

	}
	if (this->keys[GLFW_KEY_SPACE]) {
		this->isLogoMove = true;
	}
}

void Game::update(float dt) {
}

static float rotation = 0;

void Game::render(float dt) {
	
	//rotation = glm::pow(glfwGetTime(), 4);
	Renderer::getInstance()->colorBackground(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	if (this->isLogoMove) {
		moveLogo();
		return;
	}

	GameObject* triangleGameObject = GameObjectManager::getInstance()->getGameObjectByName("triangleGameObject");
	GameObject* quadGameObject = GameObjectManager::getInstance()->getGameObjectByName("quadGameObject");
	//Renderer::getInstance()->draw(*triangleGameObject, glm::vec2(this->width / 2, this->height / 2), glm::vec2(200.0f, 200.0f), rotation);

	Renderer::getInstance()->draw(*quadGameObject, glm::vec2(this->logoX, this->logoY), glm::vec2(this->logoWidth, this->logoHeight), rotation);

	this->logoX += this->logoXSpeed;
	this->logoY += this->logoYSpeed;

	if (this->logoX + this->logoWidth / 2 >= this->width || this->logoX - this->logoWidth / 2 <= 0) {
		srand(time(NULL));
		int colorIndex = rand() % 8;
		glm::vec4 dvdColor = this->colorsArray[colorIndex];

		std::cout << "Red: " << dvdColor.x << " | " << "Green: " << dvdColor.y << " | " << "Blue: " << dvdColor.z << " | " << std::endl;

		ResourceManager::getInstance()->getShaderByName("quadShader")->setVector4f("uDvdColor", dvdColor, true);
		this->logoXSpeed = -this->logoXSpeed;
	}
	if (this->logoY + this->logoHeight / 2 >= this->height || this->logoY - this->logoHeight / 2 <= 0) {
		srand(time(NULL));
		int colorIndex = rand() % 8;
		glm::vec4 dvdColor = this->colorsArray[colorIndex];

		std::cout << "Red: " << dvdColor.x << " | " << "Green: " << dvdColor.y << " | " << "Blue: " << dvdColor.z << " | " << std::endl;

		ResourceManager::getInstance()->getShaderByName("quadShader")->setVector4f("uDvdColor", dvdColor, true);
		this->logoYSpeed = -this->logoYSpeed;
	}
}
void Game::clear() {

}