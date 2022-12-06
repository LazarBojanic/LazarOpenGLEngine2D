#include "Game.hpp"

Game* Game::instance;

Game::Game(GLFWwindow* window, unsigned int width, unsigned int height) {
	this->window = window;
	this->gameState = SCREEN_SAVER;
	this->width = width;
	this->height = height;
	this->keys = new bool[1024];
	initKeys();
	this->startTime = glfwGetTime();
}
Game::~Game() {
	delete[] this->keys;
	delete[] this->colorsArray;
	delete this->enemies;
}

Game* Game::getInstance(GLFWwindow* window, unsigned int width, unsigned int height) {
	if (!instance) {
		instance = new Game(window, width, height);
	}
	return instance;
}
void Game::updateWindowSize(int width, int height) {
	this->width = width;
	this->height = height;
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

	this->dvdTransitionSpeed = 200.0f;
	this->dvdDestinationX = this->width / 2.0f;
	this->dvdDestinationY = 50.0f;
	

	this->dvdRotationWhileTransition = 0.0f;
	this->dvdRotationWhileTransitionSpeed = 300.0f;
	this->dvdScaleWhileTransition = 1.0f;
	this->destinationScale = 0.4f;
	this->deltaScale = 1.0f;

	this->numberOfLines = 1;
	this->numberOfEnemiesPerLine = 4;
	this->enemies = new std::vector<GameObject*>();
	this->randomEnemyProjectileSpawnTime = new int[6] {
		4, 5, 6, 7, 8, 9
	};

	this->laserIsShooting = false;

	this->score = 0;
}
void Game::initResources() {
	glm::mat4 projection = glm::ortho(0.0f, (float)this->width, 0.0f, (float)this->height, -1.0f, 1.0f);

	Quad* quad = new Quad();
	
	Mesh* dvdMesh = ResourceManager::getInstance()->addMesh(*quad, "dvdMesh", 0, 3, 1, 3, 2, 2);
	Mesh* backgroundMesh = ResourceManager::getInstance()->addMesh(*quad, "backgroundMesh", 0, 3, 1, 3, 2, 2);
	Mesh* bluRayMesh = ResourceManager::getInstance()->addMesh(*quad, "bluRayMesh", 0, 3, 1, 3, 2, 2);
	Mesh* laserMesh = ResourceManager::getInstance()->addMesh(*quad, "laserMesh", 0, 3, 1, 3, 2, 2);
	
	Shader* dvdShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOPBetterAbstraction\\assets\\shaders\\dvdVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOPBetterAbstraction\\assets\\shaders\\dvdBurnFragmentShader.glsl", "dvdShader");
	Shader* backgroundShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOPBetterAbstraction\\assets\\shaders\\backgroundVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOPBetterAbstraction\\assets\\shaders\\backgroundFragmentShader.glsl", "backgroundShader");
	Shader* bluRayShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOPBetterAbstraction\\assets\\shaders\\bluRayVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOPBetterAbstraction\\assets\\shaders\\bluRayFragmentShader.glsl", "bluRayShader");
	Shader* laserShader = ResourceManager::getInstance()->addShader("D:\\CPP\\LazarOpenGLEngineOOPBetterAbstraction\\assets\\shaders\\laserVertexShader.glsl", "D:\\CPP\\LazarOpenGLEngineOOPBetterAbstraction\\assets\\shaders\\laserFragmentShader.glsl", "laserShader");
	

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
	
	Texture2D* dvdTexture = ResourceManager::getInstance()->addTexture2D("D:\\CPP\\LazarOpenGLEngineOOPBetterAbstraction\\assets\\textures\\dvdLogo.png", true, "dvdTexture");
	Texture2D* bluRayTexture = ResourceManager::getInstance()->addTexture2D("D:\\CPP\\LazarOpenGLEngineOOPBetterAbstraction\\assets\\textures\\bluRayLogo.png", true, "bluRayTexture");
	Texture2D* laserTexture = ResourceManager::getInstance()->addTexture2D("D:\\CPP\\LazarOpenGLEngineOOPBetterAbstraction\\assets\\textures\\laser.png", true, "laserTexture");

	ResourceManager::getInstance()->addDrawData("bluRayDrawData", *bluRayMesh, *bluRayShader, *bluRayTexture);

	GameObjectManager::getInstance()->addGameObject("laserGameObject", *laserMesh, *laserShader, *laserTexture, 9999.0f, 9999.0f, 20.0f, 15.0f, 1.0f, 0.0f, 0.0f, 450.0f, false);
	GameObjectManager::getInstance()->addGameObject("dvdGameObject", *dvdMesh, *dvdShader, *dvdTexture, this->width / 2 + 50.0f, this->height / 2 + 50.0f, 160.0f, 120.0f, 1.0f, 0.0f, 200.0f, 200.0f, false);
	GameObjectManager::getInstance()->addGameObject("backgroundGameObject", *backgroundMesh, *backgroundShader, *dvdTexture, this->width / 2, this->height / 2, this->width, this->height, 1.0f, 0.0f, 0.0f, 0.0f, false);
	GameObjectManager::getInstance()->addGameObject("bluRayGameObject", *bluRayMesh, *bluRayShader, *bluRayTexture, 60.0f, this->height - 45.0f, 80.0f, 60.0f, 1.0f, 0.0f, 0.0f, 0.0f, false);
}
void Game::init() {
	initVariables();
	initResources();
}
void Game::processInput(float dt) {
	GameObject* dvdGameObject = GameObjectManager::getInstance()->getGameObjectByName("dvdGameObject");
	GameObject* laserGameObject = GameObjectManager::getInstance()->getGameObjectByName("laserGameObject");
	
	if (this->gameState == ACTIVE) {
		if (this->keys[GLFW_KEY_LEFT] || this->keys[GLFW_KEY_A]) {
			dvdGameObject->setPositionX(dvdGameObject->getPositionX() - dvdGameObject->getSpeedX() * dt);
		}
		if (this->keys[GLFW_KEY_RIGHT] || this->keys[GLFW_KEY_D]) {
			dvdGameObject->setPositionX(dvdGameObject->getPositionX() + dvdGameObject->getSpeedX() * dt);
		}
		if (this->keys[GLFW_KEY_SPACE]) {
			this->laserIsShooting = true;
		}
		if (this->keys[GLFW_KEY_F]) {
			dvdGameObject->getDrawData()->getShader()->setFloat("uStartTime", glfwGetTime(), true);
			dvdGameObject->getDrawData()->getShader()->setBool("uDestroyed", true, true);
		}
	}
	if (this->gameState == SCREEN_SAVER) {
		if (this->keys[GLFW_KEY_B]) {
			this->gameState = TRANSITION_TO_ACTIVE;
			this->deltaX = this->dvdDestinationX - dvdGameObject->getPositionX();
			this->deltaY = this->dvdDestinationY - dvdGameObject->getPositionY();
			this->deltaVector = glm::sqrt(glm::pow(this->deltaX, 2.0f) + glm::pow(this->deltaY, 2.0f));
			this->deltaScale = 1.0f - this->destinationScale;
		}
		if (this->keys[GLFW_KEY_R]) {
			dvdGameObject->setPositionX(this->width / 2 + 50.0f);
			dvdGameObject->setPositionY(this->height / 2 + 50.0f);
		}
	}
}
void Game::update(float dt) {
}
void Game::updateLaser(GameObject& laserGameObject, GameObject& dvdGameObject, float dt) {
	/*GameObject* dvdGameObject = GameObjectManager::getInstance()->getGameObjectByName("dvdGameObject");
	GameObject* laserGameObject = GameObjectManager::getInstance()->getGameObjectByName("laserGameObject");
	if (laserGameObject == nullptr) {
		DrawData* laserDrawData = ResourceManager::getInstance()->getDrawDataByName("laserDrawData");
		laserGameObject = GameObjectManager::getInstance()->addGameObject("laserGameObject", *laserDrawData, dvdGameObject->getPositionX(), dvdGameObject->getPositionY() + dvdGameObject->getSizeY(),
			20.0f, 15.0f, 1.0f, 0.0f, 0.0f, 450.0f, false);
	}
	if (this->laserIsShooting) {
		laserGameObject->setPositionY(laserGameObject->getPositionY() + laserGameObject->getSpeedY() * dt);
		Renderer::getInstance()->draw(*laserGameObject, true);
		if (laserGameObject->getPositionX() >= this->width || laserGameObject->getPositionX() <= 0 ||
			laserGameObject->getPositionY() >= this->height || laserGameObject->getPositionY() <= 0) {
			this->laserIsShooting = false;
			//GameObjectManager::getInstance()->removeGameObject(laserGameObject);
		}
	}*/
	if (this->laserIsShooting) {
		laserGameObject.setPositionY(laserGameObject.getPositionY() + laserGameObject.getSpeedY() * dt);
		Renderer::getInstance()->draw(laserGameObject, true);
		if (laserGameObject.getPositionX() >= this->width || laserGameObject.getPositionX() <= 0 ||
			laserGameObject.getPositionY() >= this->height || laserGameObject.getPositionY() <= 0) {
			this->laserIsShooting = false;
		}
	}
	if (!this->laserIsShooting) {
		laserGameObject.setPositionX(dvdGameObject.getPositionX());
		laserGameObject.setPositionY(dvdGameObject.getPositionY() + (dvdGameObject.getSizeY()) / 2 + 20.0f);
	}
}

void Game::render(float dt) {
	GameObject* dvdGameObject = GameObjectManager::getInstance()->getGameObjectByName("dvdGameObject");
	GameObject* backgroundGameObject = GameObjectManager::getInstance()->getGameObjectByName("backgroundGameObject");
	GameObject* laserGameObject = GameObjectManager::getInstance()->getGameObjectByName("laserGameObject");
	backgroundGameObject->getDrawData()->getShader()->setFloat("uTime", glfwGetTime(), true);
	dvdGameObject->getDrawData()->getShader()->setFloat("uTime", glfwGetTime(), true);
	
	Renderer::getInstance()->colorBackground(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Renderer::getInstance()->drawUntextured(*backgroundGameObject, true);
	if (this->gameState == SCREEN_SAVER) {
		dvdGameObject->setPositionX(dvdGameObject->getPositionX() + dvdGameObject->getSpeedX() * dt);
		dvdGameObject->setPositionY(dvdGameObject->getPositionY() + dvdGameObject->getSpeedY() * dt);
		if (dvdGameObject->getPositionX() + dvdGameObject->getScaledSizeX() / 2 >= this->width - 4.0f || dvdGameObject->getPositionX() - dvdGameObject->getScaledSizeX() / 2 <= 4.0f) {
			srand(time(NULL));
			int colorIndex = rand() % 8;
			glm::vec4 dvdColor = this->colorsArray[colorIndex];
			dvdGameObject->getDrawData()->getShader()->setVector4f("uColor", dvdColor, true);
			dvdGameObject->setSpeedX(-dvdGameObject->getSpeedX());
		}
		if (dvdGameObject->getPositionY() + dvdGameObject->getScaledSizeX() / 2 >= this->height - 4.0f || dvdGameObject->getPositionY() - dvdGameObject->getScaledSizeX() / 2  <= 4.0f) {
			srand(time(NULL));
			int colorIndex = rand() % 8;
			glm::vec4 dvdColor = this->colorsArray[colorIndex];
			dvdGameObject->getDrawData()->getShader()->setVector4f("uColor", dvdColor, true);
			dvdGameObject->setSpeedY(-dvdGameObject->getSpeedY());
		}
		Renderer::getInstance()->draw(*dvdGameObject, true);
	}
	else if (this->gameState == TRANSITION_TO_ACTIVE) {
		dvdGameObject->setRotation(dvdGameObject->getRotation() + this->dvdRotationWhileTransitionSpeed * dt);
		dvdGameObject->setScale(dvdGameObject->getScale() - ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaScale) * dt);
		dvdGameObject->setPositionX(dvdGameObject->getPositionX() + ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaX) * dt);
		dvdGameObject->setPositionY(dvdGameObject->getPositionY() + ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaY) * dt);
		Renderer::getInstance()->draw(*dvdGameObject, true);
		if (glm::abs(dvdGameObject->getPositionX() - this->dvdDestinationX) <= 4.0f && glm::abs(dvdGameObject->getPositionY() - this->dvdDestinationY) <= 4.0f) {
			this->gameState = ACTIVE;
			dvdGameObject->setRotation(0.0f);
			dvdGameObject->setSpeedX(300.0f);
			dvdGameObject->setScale(this->destinationScale);
			/*laserGameObject->setPositionX(dvdGameObject->getPositionX());
			laserGameObject->setPositionY(dvdGameObject->getPositionY());*/
			dvdGameObject->getDrawData()->getShader()->setVector4f("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);
			spawnEnemies(this->numberOfLines, this->numberOfEnemiesPerLine);
		}
	}
	else if (this->gameState == ACTIVE) {
		spawnEnemyProjectiles();
		updateEnemies();
		Renderer::getInstance()->draw(*dvdGameObject, true);

		updateLaser(*laserGameObject, *dvdGameObject, dt);
		checkCollisions();
		if (this->score == this->enemies->size()) {
			this->gameState = WIN;
			this->windowTitle = "WIN";
			glfwSetWindowTitle(this->window, this->windowTitle.c_str());
			this->dvdDestinationX = (this->width / 2 + 50.0f);
			this->dvdDestinationY = (this->height / 2 + 50.0f);
			this->deltaX = this->dvdDestinationX - dvdGameObject->getPositionX();
			this->deltaY = this->dvdDestinationY - dvdGameObject->getPositionY();
			this->deltaVector = glm::sqrt(glm::pow(this->deltaX, 2.0f) + glm::pow(this->deltaY, 2.0f));
			this->destinationScale = 1.0f;
			this->deltaScale = dvdGameObject->getScale() - this->destinationScale;
			
		}
	}
	else if (this->gameState == WIN) {
		dvdGameObject->setRotation(dvdGameObject->getRotation() + this->dvdRotationWhileTransitionSpeed * dt);
		dvdGameObject->setScale(dvdGameObject->getScale() - ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaScale) * dt);
		dvdGameObject->setPositionX(dvdGameObject->getPositionX() + ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaX) * dt);
		dvdGameObject->setPositionY(dvdGameObject->getPositionY() + ((this->dvdTransitionSpeed / this->deltaVector) * this->deltaY) * dt);
		Renderer::getInstance()->draw(*dvdGameObject, true);
		if (glm::abs(dvdGameObject->getPositionX() - this->dvdDestinationX) <= 4.0f && glm::abs(dvdGameObject->getPositionY() - this->dvdDestinationY) <= 4.0f) {
			this->gameState = SCREEN_SAVER;
			dvdGameObject->setScale(this->destinationScale);
			dvdGameObject->setRotation(0.0f);
			initVariables();
		}
	}
	else if (this->gameState == LOSS) {
		this->windowTitle = "GAME OVER";
		initVariables();
		glfwSetWindowTitle(this->window, this->windowTitle.c_str());
		this->gameState = SCREEN_SAVER;
	}
}
void Game::clear() {
	delete[] this->keys;
	delete[] this->colorsArray;
	delete this->enemies;
}
void Game::updateEnemies() {
	for (int i = 0; i < this->enemies->size(); i++) {
		if (!this->enemies->at(i)->getIsHit()) {
			this->enemies->at(i)->getDrawData()->getShader()->setVector4f("uColor", glm::vec4(0.125f, 0.4f, 0.95f, 1.0f), true);
			Renderer::getInstance()->draw(*this->enemies->at(i), false);
		}
	}
}
void Game::spawnEnemies(int numberOfLines, int numberOfEnemiesPerLine) {
	DrawData* bluRayDrawData = ResourceManager::getInstance()->getDrawDataByName("bluRayDrawData");
	float bluRaySizeX = 60.0f;
	float bluRaySizeY = 45.0f;
	float initialEnemyX = 60.0f;
	float currentEnemyX = 60.0f;
	float currentEnemyY = this->height - 45.0f;
	for (int i = 0; i < numberOfLines; i++) {
		for (int j = 0; j < numberOfEnemiesPerLine; j++) {
			GameObject* gameObject = new GameObject("enemy" + std::to_string(i * numberOfEnemiesPerLine + j), *bluRayDrawData, currentEnemyX, currentEnemyY, bluRaySizeX, bluRaySizeY, 1.0f, 0.0f, 0.0f, 0.0f, false);
			this->enemies->push_back(gameObject);
			currentEnemyX += (bluRaySizeX * 2.2f);
		}
		currentEnemyX = initialEnemyX;
		currentEnemyY -= (bluRaySizeY * 1.5f);
	}
}
void Game::checkCollisions() {
	bool foundCollision = false;
	GameObject* dvdGameObject = GameObjectManager::getInstance()->getGameObjectByName("laserGameObject");
	for (int i = 0; i < this->enemies->size(); i++) {
		GameObject* laserGameObject = GameObjectManager::getInstance()->getGameObjectByName("laserGameObject");
		bool collisionX = this->enemies->at(i)->getPositionX() + this->enemies->at(i)->getSizeX() >= laserGameObject->getPositionX() && laserGameObject->getPositionX() + laserGameObject->getSizeX() >= this->enemies->at(i)->getPositionX();
		bool collisionY = this->enemies->at(i)->getPositionY() + this->enemies->at(i)->getSizeY() >= laserGameObject->getPositionY() && laserGameObject->getPositionY() + laserGameObject->getSizeY() >= this->enemies->at(i)->getPositionY();
		if (collisionX && collisionY) {
			this->enemies->at(i)->setIsHit(true);
			this->enemies->at(i)->setPositionX(9999.0f);
			this->enemies->at(i)->setPositionY(9999.0f);
			this->score++;
			this->windowTitle = "Score: " + std::to_string(this->score);
			glfwSetWindowTitle(this->window, this->windowTitle.c_str());
			this->laserIsShooting = false;
		}
	}
}

void Game::spawnEnemyProjectiles(){
	double currentTime = glfwGetTime();
	int randomTimeDifference = this->randomEnemyProjectileSpawnTime[rand() % 6];
	int timePassed = currentTime - this->startTime;
	if (timePassed % randomTimeDifference == 0) {
		std::cout << "Spawned Projectile!" << std::endl;
	}
}
