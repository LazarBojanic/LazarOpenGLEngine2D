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
	Shader* dvdShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\dvdVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\dvdFragmentShader.glsl", "dvdShader");
	Shader* genericShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\genericVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\genericFragmentShader.glsl", "genericShader");
	Shader* bluRayShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\bluRayVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\bluRayFragmentShader.glsl", "bluRayShader");
	Texture2D* dvdTexture = ResourceManager::getInstance()->addTexture2D("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\textures\\dvdLogo.png", true, "dvdTexture");
	Texture2D* bluRayTexture = ResourceManager::getInstance()->addTexture2D("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\textures\\bluRayLogo.png", true, "bluRayTexture");
	Quad* quad = new Quad();
	Mesh* dvdMesh = new Mesh(*quad, "dvdMesh", 0, 3, 1, 3, 2, 2);
	Mesh* squareMesh = new Mesh(*quad, "squareMesh", 0, 3, 1, 3, 2, 2);
	Mesh* bluRayMesh = new Mesh(*quad, "bluRayMesh", 0, 3, 1, 3, 2, 2);
	dvdShader->setVector4f("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);
	dvdShader->setMatrix4f("uProjection", projection, true);
	dvdShader->setInt("uTexture", 0, true);

	bluRayShader->setVector4f("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);
	bluRayShader->setMatrix4f("uProjection", projection, true);
	bluRayShader->setInt("uTexture", 0, true);

	genericShader->setMatrix4f("uProjection", projection, true);
	genericShader->setVector2f("uResolution", glm::vec2(this->width, this->height), true);

	GameObject* dvdGameObject = new GameObject("dvdGameObject", *dvdMesh, *bluRayShader, *dvdTexture);
	GameObject* squareGameObject = new GameObject("squareGameObject", *squareMesh, *genericShader, *dvdTexture);
	GameObject* bluRayGameObject = new GameObject("bluRayGameObject", *bluRayMesh, *bluRayShader, *bluRayTexture);
	
	//GameObjectManager::getInstance()->addGameObject();
	GameObjectManager::getInstance()->addGameObject(*dvdGameObject);
	GameObjectManager::getInstance()->addGameObject(*squareGameObject);
	GameObjectManager::getInstance()->addGameObject(*bluRayGameObject);

	this->dvdWidth = 160.0f;
	this->dvdHeight = 120.0f;

	this->dvdX = 400.0f;
	this->dvdY = 450.0f;
	this->dvdXSpeed = 200.0f;
	this->dvdYSpeed = 200.0f;
	this->dvdGameSpeed = 400.0f;

	this->dvdRotationWhileTransition = 0.0f;
	this->dvdRotationWhileTransitionSpeed = 300.0f;
	this->dvdScaleWhileTransition = 1.0f;
	this->destinationScale = 0.4f;
	this->deltaScale = 1.0f;

	this->bluRayWidth = 40.0f;
	this->bluRayHeight = 30.0f;
	this->bluRayX = this->bluRayWidth;
	this->bluRayY = this->height - this->bluRayHeight;
	this->bluRayXSpeed = 3.0f;
	this->bluRayYSpeed = 3.0f;

	this->dvdDestinationX = this->width / 2.0f;
	this->dvdDestinationY = 25.0f + ((this->dvdHeight * this->destinationScale) / 2.0f);
	this->dvdTransitionSpeed = 200.0f;
}


void Game::processInput(float dt) {
	if (this->gameState == ACTIVE) {
		if (this->keys[GLFW_KEY_LEFT]) {
			this->dvdX -= this->dvdGameSpeed * dt;
		}
		if (this->keys[GLFW_KEY_RIGHT]) {
			std::cout << dt << std::endl;
			this->dvdX += this->dvdGameSpeed * dt;
		}
		if (this->keys[GLFW_KEY_SPACE]) {
			//shootLaser();
		}
	}
	if (this->gameState == SCREEN_SAVER) {
		if (this->keys[GLFW_KEY_B]) {
			this->gameState = TRANSITION_TO_ACTIVE;
			this->deltaX = this->dvdDestinationX - this->dvdX;
			this->deltaY = this->dvdDestinationY - this->dvdY;
			this->deltaVector = glm::sqrt(glm::pow(this->deltaX, 2.0f) + glm::pow(this->deltaY, 2.0f));
			this->deltaScale = 1 - this->destinationScale;
		}
	}
}
void Game::update(float dt) {
}
void Game::spawnEnemyLine(GameObject& gameObject, int numberOfEnemies) {
	float currentEnemyX = this->bluRayX;
	float currentEnemyY = this->bluRayY;

	for (int i = 0; i < numberOfEnemies; i++) {
		gameObject.getShader()->setVector4f("uColor", glm::vec4(0.2f, 0.2f, 0.8f, 1.0f), true);
		Renderer::getInstance()->draw(gameObject, glm::vec2(currentEnemyX, currentEnemyY), glm::vec2(this->bluRayWidth, this->bluRayHeight), 0);
		currentEnemyX += (this->bluRayWidth * 1.5f);
	}
}

void Game::render(float dt) {
	GameObject* dvdGameObject = GameObjectManager::getInstance()->getGameObjectByName("dvdGameObject");
	GameObject* squareGameObject = GameObjectManager::getInstance()->getGameObjectByName("squareGameObject");
	GameObject* bluRayGameObject = GameObjectManager::getInstance()->getGameObjectByName("bluRayGameObject");
	squareGameObject->getShader()->setFloat("uTime", glfwGetTime(), true);
	
	
	Renderer::getInstance()->colorBackground(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Renderer::getInstance()->drawUntextured(*squareGameObject, glm::vec2(this->width / 2, this->height / 2), glm::vec2(this->width, this->height), 0);
	if (this->gameState == SCREEN_SAVER) {
		this->dvdX += this->dvdXSpeed * dt;
		this->dvdY += this->dvdYSpeed * dt;
		if (this->dvdX + this->dvdWidth / 2 >= this->width || this->dvdX - this->dvdWidth / 2 <= 0) {
			srand(time(NULL));
			int colorIndex = rand() % 8;
			glm::vec4 dvdColor = this->colorsArray[colorIndex];
			dvdGameObject->getShader()->setVector4f("uColor", dvdColor, true);
			this->dvdXSpeed = -this->dvdXSpeed;
		}
		if (this->dvdY + this->dvdHeight / 2 >= this->height || this->dvdY - this->dvdHeight / 2 <= 0) {
			srand(time(NULL));
			int colorIndex = rand() % 8;
			glm::vec4 dvdColor = this->colorsArray[colorIndex];
			dvdGameObject->getShader()->setVector4f("uColor", dvdColor, true);
			this->dvdYSpeed = -this->dvdYSpeed;
		}
		Renderer::getInstance()->draw(*dvdGameObject, glm::vec2(this->dvdX, this->dvdY), glm::vec2(this->dvdWidth, this->dvdHeight), 0);
		
	}
	else if (this->gameState == TRANSITION_TO_ACTIVE) {
		this->dvdRotationWhileTransition += this->dvdRotationWhileTransitionSpeed * dt;
		this->dvdScaleWhileTransition -= ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaScale) * dt;
		this->dvdX += ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaX) * dt;
		this->dvdY += ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaY) * dt;	
		Renderer::getInstance()->draw(*dvdGameObject, glm::vec2(this->dvdX, this->dvdY), glm::vec2(this->dvdWidth * this->dvdScaleWhileTransition, this->dvdHeight * this->dvdScaleWhileTransition), this->dvdRotationWhileTransition);
		if (glm::abs(this->dvdX - this->dvdDestinationX) <= 3.0f && glm::abs(this->dvdY - this->dvdDestinationY) <= 3.0f) {
			this->gameState = ACTIVE;
			this->dvdWidth *= this->destinationScale;
			this->dvdHeight *= this->destinationScale;
		}
	}
	else if (this->gameState == ACTIVE) {
		srand(time(NULL));
		int numberOfEnemies = rand() % 8 + 2;
		spawnEnemyLine(*bluRayGameObject, numberOfEnemies);
		dvdGameObject->getShader()->setVector4f("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);
		Renderer::getInstance()->draw(*dvdGameObject, glm::vec2(this->dvdX, this->dvdY), glm::vec2(this->dvdWidth, this->dvdHeight), 0);
		//Renderer::getInstance()->draw(*projectileGameObject, glm::vec2(this->logoX, this->logoY + 30.0f), glm::vec2(30.0f, 30.0f), 0);

	}
	else if (this->gameState == WIN) {

	}
	else if (this->gameState == LOSS) {

	}
	std::cout << "Width : " << width << " Height: " << height << std::endl;
}
void Game::clear() {

}
void Game::updateWindowSize(int width, int height) {
	this->width = width;
	this->height = height;
}