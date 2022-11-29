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
	delete this->colorsArray;
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

	this->x = 400.0f;
	this->y = 450.0f;
	this->xSpeed = 3.0f;
	this->ySpeed = 3.0f;
}


void Game::processInput(float dt) {
	if (this->keys[GLFW_KEY_UP]) {

	}
	if (this->keys[GLFW_KEY_DOWN]) {

	}
}

void Game::update(float dt) {
}

static float rotation = 0;

void Game::render(float dt) {
	//rotation = glm::pow(glfwGetTime(), 4);
	Renderer::getInstance()->colorBackground(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	GameObject* triangleGameObject = GameObjectManager::getInstance()->getGameObjectByName("triangleGameObject");
	GameObject* quadGameObject = GameObjectManager::getInstance()->getGameObjectByName("quadGameObject");
	//Renderer::getInstance()->draw(*triangleGameObject, glm::vec2(this->width / 2, this->height / 2), glm::vec2(200.0f, 200.0f), rotation);

	Renderer::getInstance()->draw(*quadGameObject, glm::vec2(this->x, this->y), glm::vec2(this->logoWidth, this->logoHeight), rotation);

	this->x += this->xSpeed;
	this->y += this->ySpeed;

	if (this->x + this->logoWidth / 2 >= this->width || this->x - this->logoWidth / 2 <= 0) {
		srand(time(NULL));
		int colorIndex = rand() % 8;
		glm::vec4 dvdColor = this->colorsArray[colorIndex];

		std::cout << "Red: " << dvdColor.x << " | " << "Green: " << dvdColor.y << " | " << "Blue: " << dvdColor.z << " | " << std::endl;

		ResourceManager::getInstance()->getShaderByName("quadShader")->setVector4f("uDvdColor", dvdColor, true);
		this->xSpeed = -this->xSpeed;
	}
	if (this->y + this->logoHeight / 2 >= this->height || this->y - this->logoHeight / 2 <= 0) {
		srand(time(NULL));
		int colorIndex = rand() % 8;
		glm::vec4 dvdColor = this->colorsArray[colorIndex];

		std::cout << "Red: " << dvdColor.x << " | " << "Green: " << dvdColor.y << " | " << "Blue: " << dvdColor.z << " | " << std::endl;

		ResourceManager::getInstance()->getShaderByName("quadShader")->setVector4f("uDvdColor", dvdColor, true);
		this->ySpeed = -this->ySpeed;
	}
}
void Game::clear() {

}