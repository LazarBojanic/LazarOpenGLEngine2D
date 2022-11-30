#include "Game.hpp"

Game* Game::instance;

Game::Game(unsigned int width, unsigned int height) {
	this->gameState = SCREEN_SAVER;
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
Game* Game::getInstance() {
	if (!instance) {
		instance = new Game(0, 0);
	}
	return instance;
}

void Game::init() {
	glm::mat4 projection = glm::ortho(0.0f, (float)this->width, 0.0f, (float)this->height, -1.0f, 1.0f);
	//Shader* triangleShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\triangleVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\triangleFragmentShader.glsl", "triangleShader");
	Shader* quadShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\quadVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\quadFragmentShader.glsl", "quadShader");
	Texture2D* quadTexture = ResourceManager::getInstance()->addTexture2D("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\textures\\dvdLogo.png", true, "quadTexture");
	//Triangle* triangle = new Triangle();
	Quad* quad = new Quad();
	
	
	/*Mesh* triangleMesh = new Mesh(*triangle, "triangleMesh", 0, 3, 1, 3, 2, 2);
	triangleShader->setMatrix4f("uProjection", projection, true);
	GameObject* triangleGameObject = new GameObject("triangleGameObject", *triangleMesh, *triangleShader, *quadTexture);
	GameObjectManager::getInstance()->addGameObject(*triangleGameObject);*/

	Mesh* quadMesh = new Mesh(*quad, "quadMesh", 0, 3, 1, 3, 2, 2);
	quadShader->setVector4f("uDvdColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);
	quadShader->setMatrix4f("uProjection", projection, true);
	quadShader->setInt("uTexture", 0, true);
	GameObject* quadGameObject = new GameObject("quadGameObject", *quadMesh, *quadShader, *quadTexture);
	GameObjectManager::getInstance()->addGameObject(*quadGameObject);

	this->isLogoMove = false;
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
		this->gameState = TRANSITION_TO_ACTIVE;
	}
}

void Game::update(float dt) {
}

void Game::render(float dt) {
	GameObject* quadGameObject = GameObjectManager::getInstance()->getGameObjectByName("quadGameObject");
	Shader* quadShader = ResourceManager::getInstance()->getShaderByName("quadShader");
	Renderer::getInstance()->colorBackground(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	if (this->gameState == SCREEN_SAVER) {
		this->logoX += this->logoXSpeed;
		this->logoY += this->logoYSpeed;
		if (this->logoX + this->logoWidth / 2 >= this->width || this->logoX - this->logoWidth / 2 <= 0) {
			srand(time(NULL));
			int colorIndex = rand() % 8;
			glm::vec4 dvdColor = this->colorsArray[colorIndex];
			quadShader->setVector4f("uDvdColor", dvdColor, true);
			this->logoXSpeed = -this->logoXSpeed;
		}
		if (this->logoY + this->logoHeight / 2 >= this->height || this->logoY - this->logoHeight / 2 <= 0) {
			srand(time(NULL));
			int colorIndex = rand() % 8;
			glm::vec4 dvdColor = this->colorsArray[colorIndex];
			quadShader->setVector4f("uDvdColor", dvdColor, true);
			this->logoYSpeed = -this->logoYSpeed;
		}
		Renderer::getInstance()->draw(*quadGameObject, glm::vec2(this->logoX, this->logoY), glm::vec2(this->logoWidth, this->logoHeight), 0);
	}
	else if (this->gameState == TRANSITION_TO_ACTIVE) {
		float destinationX = this->width / 2.0f;
		float destinationY = 25.0f + (this->logoHeight / 2.0f);
		float deltaX = this->logoX - destinationX;
		float deltaY = this->logoY - destinationY;
		if (deltaX > 0) {
			this->logoX -= 3;
		}
		if (deltaX < 0) {
			this->logoX += 3;
		}
		if (deltaY > 0) {
			this->logoY -= 3;
		}
		if (deltaY < 0) {
			this->logoY += 3;
		}
		Renderer::getInstance()->draw(*quadGameObject, glm::vec2(this->logoX, this->logoY), glm::vec2(this->logoWidth, this->logoHeight), 0);
		//std::cout << "X: " << glm::abs(this->logoX - destinationX) << "Y: " << glm::abs(this->logoY - destinationY) << std::endl;
		if (glm::abs(this->logoX - destinationX) <= 3.0f && glm::abs(this->logoY - destinationY) <= 3.0f) {
			this->gameState = ACTIVE;
			//std::cout << "ACTIVE!" << std::endl;
		}
	}
	else if (this->gameState == ACTIVE) {
		//std::cout << "X: " << glm::abs(this->logoX) << "Y: " << glm::abs(this->logoY) << std::endl;
		Renderer::getInstance()->draw(*quadGameObject, glm::vec2(this->logoX, this->logoY), glm::vec2(this->logoWidth, this->logoHeight), 0);
	}
	else if (this->gameState == WIN) {

	}
	else if (this->gameState == LOSS) {

	}	
}
void Game::clear() {

}