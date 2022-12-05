#include "Game.hpp"

Game* Game::instance;

Game::Game(GLFWwindow* window, unsigned int width, unsigned int height) {
	this->window = window;
	this->gameState = SCREEN_SAVER;
	this->width = width;
	this->height = height;
	this->keys = new bool[1024];
	initKeys();
}
Game::~Game() {
	delete[] this->keys;
	delete[] this->colorsArray;
	delete[] this->enemyPositions;
	delete[] this->enemies;
}

Game* Game::getInstance(GLFWwindow* window, unsigned int width, unsigned int height) {
	if (!instance) {
		instance = new Game(window, width, height);
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
		instance = new Game(nullptr, 0, 0);
	}
	return instance;
}
void Game::init() {
	initResources();
	initVariables();
}
void Game::initResources() {
	glm::mat4 projection = glm::ortho(0.0f, (float)this->width, 0.0f, (float)this->height, -1.0f, 1.0f);

	Shader* dvdShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\dvdVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\dvdBurnFragmentShader.glsl", "dvdShader");
	Shader* backgroundShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\backgroundVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\backgroundFragmentShader.glsl", "backgroundShader");
	Shader* bluRayShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\bluRayVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\bluRayFragmentShader.glsl", "bluRayShader");
	Shader* laserShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\laserVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOP\\assets\\shaders\\laserFragmentShader.glsl", "laserShader");
	

	Texture2D* dvdTexture = ResourceManager::getInstance()->addTexture2D("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\textures\\dvdLogo.png", true, "dvdTexture");
	Texture2D* bluRayTexture = ResourceManager::getInstance()->addTexture2D("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\textures\\bluRayLogo.png", true, "bluRayTexture");
	Texture2D* laserTexture = ResourceManager::getInstance()->addTexture2D("D:\\CPP\\LazarOpenGLEngineOOP\\assets\\textures\\laser.png", true, "laserTexture");
	
	Quad* quad = new Quad();
	
	Mesh* dvdMesh = new Mesh(*quad, "dvdMesh", 0, 3, 1, 3, 2, 2);
	Mesh* backgroundMesh = new Mesh(*quad, "backgroundMesh", 0, 3, 1, 3, 2, 2);
	Mesh* bluRayMesh = new Mesh(*quad, "bluRayMesh", 0, 3, 1, 3, 2, 2);
	Mesh* laserMesh = new Mesh(*quad, "laserMesh", 0, 3, 1, 3, 2, 2);

	dvdShader->setVector4f("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);
	dvdShader->setMatrix4f("uProjection", projection, true);
	dvdShader->setInt("uTexture", 0, true);
	dvdShader->setFloat("uDuration", 1.5f, true);
	dvdShader->setBool("uDestroyed", false, true);

	bluRayShader->setVector4f("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);
	bluRayShader->setMatrix4f("uProjection", projection, true);
	bluRayShader->setInt("uTexture", 0, true);

	backgroundShader->setMatrix4f("uProjection", projection, true);
	backgroundShader->setVector2f("uResolution", glm::vec2(this->width, this->height), true);

	laserShader->setMatrix4f("uProjection", projection, true);
	laserShader->setInt("uTexture", 0, true);

	GameObject* dvdGameObject = new GameObject("dvdGameObject", *dvdMesh, *dvdShader, *dvdTexture);
	GameObject* backgroundGameObject = new GameObject("backgroundGameObject", *backgroundMesh, *backgroundShader, *dvdTexture);
	GameObject* bluRayGameObject = new GameObject("bluRayGameObject", *bluRayMesh, *bluRayShader, *bluRayTexture);
	GameObject* laserGameObject = new GameObject("laserGameObject", *laserMesh, *laserShader, *laserTexture);

	GameObjectManager::getInstance()->addGameObject(*dvdGameObject);
	GameObjectManager::getInstance()->addGameObject(*backgroundGameObject);
	GameObjectManager::getInstance()->addGameObject(*bluRayGameObject);
	GameObjectManager::getInstance()->addGameObject(*laserGameObject);
}
void Game::initVariables() {
	glfwSetWindowTitle(this->window, "DVD Game");
	this->colorsArray = new glm::vec4[8]{
		glm::vec4(0.7f, 0.4f, 0.4f, 1.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.4f, 0.7f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(0.75f, 0.0f, 0.75f, 1.0f)
	};
	this->dvdWidth = 160.0f;
	this->dvdHeight = 120.0f;

	this->dvdX = this->width / 2 + 50.0f;
	this->dvdY = this->height / 2 + 50.0f;
	this->dvdXSpeed = 200.0f;
	this->dvdYSpeed = 200.0f;
	this->dvdGameSpeed = 400.0f;

	this->dvdRotationWhileTransition = 0.0f;
	this->dvdRotationWhileTransitionSpeed = 300.0f;
	this->dvdScaleWhileTransition = 1.0f;
	this->destinationScale = 0.4f;
	this->deltaScale = 1.0f;

	this->bluRayWidth = 60.0f;
	this->bluRayHeight = 45.0f;
	this->bluRayX = this->bluRayWidth;
	this->bluRayY = this->height - this->bluRayHeight;
	this->bluRayXSpeed = 3.0f;
	this->bluRayYSpeed = 3.0f;

	this->dvdDestinationX = this->width / 2.0f;
	this->dvdDestinationY = 25.0f + ((this->dvdHeight * this->destinationScale) / 2.0f);
	this->dvdTransitionSpeed = 200.0f;

	this->numberOfLines = 1;
	this->numberOfEnemiesPerLine = 4;
	this->enemyPositions = new std::vector<glm::vec2>();
	this->enemies = new std::vector<Entity*>();

	this->laserX = this->dvdX;
	this->laserY = this->dvdY + this->dvdHeight;
	this->laserWidth = 20.0f;
	this->laserHeight = 15.0f;
	this->laserSpeedY = 350.0f;
	this->laserIsShooting = false;

	this->score = 0;
}
void Game::processInput(float dt) {
	if (this->gameState == ACTIVE) {
		if (this->keys[GLFW_KEY_LEFT] || this->keys[GLFW_KEY_A]) {
			this->dvdX -= this->dvdGameSpeed * dt;
		}
		if (this->keys[GLFW_KEY_RIGHT] || this->keys[GLFW_KEY_D]) {
			this->dvdX += this->dvdGameSpeed * dt;
		}
		if (this->keys[GLFW_KEY_SPACE]) {
			this->laserX = this->dvdX;
			this->laserY = this->dvdY + this->dvdHeight;
			this->laserIsShooting = true;
		}
		if (this->keys[GLFW_KEY_F]) {
			GameObject* dvdGameObject = GameObjectManager::getInstance()->getGameObjectByName("dvdGameObject");
			dvdGameObject->getShader()->setFloat("uStartTime", glfwGetTime(), true);
			dvdGameObject->getShader()->setBool("uDestroyed", true, true);
		}
	}
	if (this->gameState == SCREEN_SAVER) {
		if (this->keys[GLFW_KEY_B]) {
			this->gameState = TRANSITION_TO_ACTIVE;
			this->deltaX = this->dvdDestinationX - this->dvdX;
			this->deltaY = this->dvdDestinationY - this->dvdY;
			this->deltaVector = glm::sqrt(glm::pow(this->deltaX, 2.0f) + glm::pow(this->deltaY, 2.0f));
			this->deltaScale = 1.0f - this->destinationScale;
		}
	}
}
void Game::update(float dt) {
}
void Game::updateEnemies(GameObject& bluRayGameObject) {
	for (int i = 0; i < this->enemies->size(); i++) {
		if (!this->enemies->at(i)->isHit) {
			bluRayGameObject.getShader()->setVector4f("uColor", glm::vec4(0.125f, 0.4f, 0.95f, 1.0f), true);
			Renderer::getInstance()->draw(bluRayGameObject, glm::vec2(this->enemies->at(i)->position.x, this->enemies->at(i)->position.y), glm::vec2(this->enemies->at(i)->size.x, this->enemies->at(i)->size.y), this->enemies->at(i)->rotation);
		}
	}
}
void Game::spawnEnemies(int numberOfLines, int numberOfEnemiesPerLine){
	float currentEnemyX = this->bluRayX;
	float currentEnemyY = this->bluRayY;
	for (int i = 0; i < numberOfLines; i++) {
		for (int j = 0; j < numberOfEnemiesPerLine; j++) {
			Entity* entity = new Entity("enemy" + std::to_string(i * numberOfEnemiesPerLine + j), glm::vec2(currentEnemyX, currentEnemyY), 
				glm::vec2(this->bluRayWidth, this->bluRayHeight), 0, false);
			this->enemies->push_back(entity);
			currentEnemyX += (this->bluRayWidth * 2.2f);
		}
		currentEnemyX = this->bluRayX;
		currentEnemyY -= (this->bluRayHeight * 1.5f);
	}
}
bool Game::checkCollision(Entity& entity, glm::vec2 positionTwo, glm::vec2 sizeTwo) {
	bool collisionX = entity.position.x + entity.size.x >= positionTwo.x && positionTwo.x + sizeTwo.x >= entity.position.x;
	bool collisionY = entity.position.y + entity.size.y >= positionTwo.y && positionTwo.y + sizeTwo.y >= entity.position.y;
	return collisionX && collisionY;
}
void Game::render(float dt) {
	GameObject* dvdGameObject = GameObjectManager::getInstance()->getGameObjectByName("dvdGameObject");
	GameObject* backgroundGameObject = GameObjectManager::getInstance()->getGameObjectByName("backgroundGameObject");
	GameObject* bluRayGameObject = GameObjectManager::getInstance()->getGameObjectByName("bluRayGameObject");
	GameObject* laserGameObject = GameObjectManager::getInstance()->getGameObjectByName("laserGameObject");
	backgroundGameObject->getShader()->setFloat("uTime", glfwGetTime(), true);
	dvdGameObject->getShader()->setFloat("uTime", glfwGetTime(), true);
	
	Renderer::getInstance()->colorBackground(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Renderer::getInstance()->drawUntextured(*backgroundGameObject, glm::vec2(this->width / 2, this->height / 2), glm::vec2(this->width, this->height), 0);
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
		if (this->dvdY + (this->dvdHeight / 2) - 3.0f>= this->height || this->dvdY - (this->dvdHeight / 2) + 3.0f <= 0) {
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
			this->laserX = this->dvdX;
			this->laserY = this->dvdY + this->dvdHeight;
			dvdGameObject->getShader()->setVector4f("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);
			spawnEnemies(this->numberOfLines, this->numberOfEnemiesPerLine);
		}
	}
	else if (this->gameState == ACTIVE) {
		updateEnemies(*bluRayGameObject);
		Renderer::getInstance()->draw(*dvdGameObject, glm::vec2(this->dvdX, this->dvdY), glm::vec2(this->dvdWidth, this->dvdHeight), 0);
		if (this->laserIsShooting) {
			this->laserY += this->laserSpeedY * dt;
			Renderer::getInstance()->draw(*laserGameObject, glm::vec2(this->laserX, this->laserY), glm::vec2(this->laserWidth, this->laserHeight), 0);
		}
		if (this->laserX >= this->width ||  this->laserX <= 0 || this->laserY >= this->height || this->laserY <= 0) {
			this->laserX = this->dvdX;
			this->laserY = this->dvdY + this->dvdHeight;
			this->laserIsShooting = false;
		}
		for (int i = 0; i < this->enemies->size(); i++) {
			if (checkCollision(*this->enemies->at(i),
				glm::vec2(this->laserX, this->laserY),
				glm::vec2(this->laserWidth, this->laserHeight))) {
				std::cout << "Collision detected with " << this->enemies->at(i)->name << std::endl;
				this->enemies->at(i)->isHit = true;
				this->enemies->at(i)->position.x = this->dvdX;
				this->enemies->at(i)->position.y = this->dvdY;
				this->score++;
				this->windowTitle = "Score: " + std::to_string(this->score);
				glfwSetWindowTitle(this->window, this->windowTitle.c_str());
				this->laserX = this->dvdX;
				this->laserY = this->dvdY + this->dvdHeight;
				this->laserIsShooting = false;
			}
		}
		if (this->score == this->enemies->size()) {
			this->gameState = WIN;
			this->windowTitle = "WIN";
			glfwSetWindowTitle(this->window, this->windowTitle.c_str());
			this->dvdDestinationX = (this->width / 2 + 50.0f);
			this->dvdDestinationY = (this->height / 2 + 50.0f);
			this->deltaX = this->dvdDestinationX - this->dvdX;
			this->deltaY = this->dvdDestinationY - this->dvdY;
			this->deltaVector = glm::sqrt(glm::pow(this->deltaX, 2.0f) + glm::pow(this->deltaY, 2.0f));
			this->destinationScale = 1.0f;
			this->deltaScale = this->dvdScaleWhileTransition - this->destinationScale;
		}
	}
	else if (this->gameState == WIN) {
		this->dvdRotationWhileTransition += this->dvdRotationWhileTransitionSpeed * dt;
		this->dvdScaleWhileTransition -= ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaScale) * dt;
		this->dvdX += ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaX) * dt;
		this->dvdY += ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaY) * dt;
		Renderer::getInstance()->draw(*dvdGameObject, glm::vec2(this->dvdX, this->dvdY), glm::vec2(this->dvdWidth * this->dvdScaleWhileTransition, this->dvdHeight * this->dvdScaleWhileTransition), this->dvdRotationWhileTransition);
		if (glm::abs(this->dvdX - this->dvdDestinationX) <= 3.0f && glm::abs(this->dvdY - this->dvdDestinationY) <= 3.0f) {
			this->gameState = SCREEN_SAVER;
			this->dvdWidth *= this->destinationScale;
			this->dvdHeight *= this->destinationScale;
			initVariables();
		}
	}
	else if (this->gameState == LOSS) {
		this->windowTitle = "GAME OVER";
		initVariables();
		std::cout << this->dvdX << " : " << this->dvdY << std::endl;
		glfwSetWindowTitle(this->window, this->windowTitle.c_str());
		this->gameState = SCREEN_SAVER;
	}
}
void Game::clear() {

}
void Game::updateWindowSize(int width, int height) {
	this->width = width;
	this->height = height;
}