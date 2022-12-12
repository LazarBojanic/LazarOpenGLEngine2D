#include "Game.hpp"

Game* Game::instance;

Game::Game(GLFWwindow* window, unsigned int width, unsigned int height) {
	this->workingDirectory = std::filesystem::current_path().generic_string();
	this->window = window;
	this->gameState = SCREEN_SAVER;
	this->width = width;
	this->height = height;
	this->keys = new bool[1024];
	initKeys();
	this->startTime = glfwGetTime();
	this->soundEngine = irrklang::createIrrKlangDevice();
}
Game::~Game() {
	delete[] this->keys;
	delete[] this->colorsArray;
	delete[] this->intervals;
	delete this->soundEngine;
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
	this->dvdDestinationX = this->width / 2;
	this->dvdDestinationY = 50.0f;

	this->dvdRotationWhileTransition = 0.0f;
	this->dvdRotationWhileTransitionSpeed = 300.0f;
	this->dvdScaleWhileTransition = 1.0f;
	this->destinationScale = 0.4f;
	this->deltaScale = 1.0f;

	this->numberOfLines = 3;
	this->numberOfEnemiesPerLine = 8;
	this->enemyIndexOfProjectile = 0;
	this->intervals = new float[4] {
		2.0f, 4.0, 6.0f, 8.0f
	};
	this->interval = 0.0f;

	this->laserIsShooting = false;

	this->score = 0;
	this->dvdDestructionDuration = 2.0f;

	this->lowerBound = -0.5f * PI;
	this->upperBound = 1.5f * PI;

	this->t = this->lowerBound;

	this->infinityPositionsCount = 392;
	this->infinityPositions = new std::vector<glm::vec2*>();
	this->currentInfinityPosition = 0;
	addDots(1.0f);
}
void Game::initResources() {
	glm::mat4 orthographicProjection = glm::ortho(0.0f, (float)this->width, 0.0f, (float)this->height, -1.0f, 1.0f);
	
	Quad* quad = new Quad();
	Triangle* triangle = new Triangle();

	Mesh* projectileMesh = ResourceManager::getInstance()->addMesh(*triangle, "projectileMesh", 0, 3, 1, 3, 2, 2);
	Mesh* dvdMesh = ResourceManager::getInstance()->addMesh(*quad, "dvdMesh", 0, 3, 1, 3, 2, 2);
	Mesh* backgroundMesh = ResourceManager::getInstance()->addMesh(*quad, "backgroundMesh", 0, 3, 1, 3, 2, 2);
	Mesh* bluRayMesh = ResourceManager::getInstance()->addMesh(*quad, "bluRayMesh", 0, 3, 1, 3, 2, 2);
	Mesh* laserMesh = ResourceManager::getInstance()->addMesh(*quad, "laserMesh", 0, 3, 1, 3, 2, 2);

	Mesh* dotMesh = ResourceManager::getInstance()->addMesh(*quad, "dotMesh", 0, 3, 1, 3, 2, 2);
	
	Shader* projectileShader = ResourceManager::getInstance()->addShader(workingDirectory + "\\assets\\shaders\\triangleVertexShader.glsl", workingDirectory + "\\assets\\shaders\\triangleFragmentShader.glsl", "projectileShader");
	Shader* dvdShader = ResourceManager::getInstance()->addShader(workingDirectory + "\\assets\\shaders\\dvdVertexShader.glsl", workingDirectory + "\\assets\\shaders\\dvdBurnFragmentShader.glsl", "dvdShader");
	Shader* backgroundShader = ResourceManager::getInstance()->addShader(workingDirectory + "\\assets\\shaders\\backgroundVertexShader.glsl", workingDirectory + "\\assets\\shaders\\backgroundFragmentShader.glsl", "backgroundShader");
	Shader* bluRayShader = ResourceManager::getInstance()->addShader(workingDirectory + "\\assets\\shaders\\bluRayVertexShader.glsl", workingDirectory + "\\assets\\shaders\\bluRayFragmentShader.glsl", "bluRayShader");
	Shader* laserShader = ResourceManager::getInstance()->addShader(workingDirectory + "\\assets\\shaders\\laserVertexShader.glsl", workingDirectory + "\\assets\\shaders\\laserFragmentShader.glsl", "laserShader");

	Shader* dotShader = ResourceManager::getInstance()->addShader(workingDirectory + "\\assets\\shaders\\genericVertexShader.glsl", workingDirectory + "\\assets\\shaders\\genericFragmentShader.glsl", "dotShader");

	projectileShader->setMatrix4f("uProjection", orthographicProjection, true);

	dvdShader->setVector4f("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);
	dvdShader->setMatrix4f("uProjection", orthographicProjection, true);
	dvdShader->setInt("uTexture", 0, true);
	dvdShader->setFloat("uDuration", this->dvdDestructionDuration, true);
	dvdShader->setBool("uDestroyed", false, true);

	bluRayShader->setVector4f("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);
	bluRayShader->setMatrix4f("uProjection", orthographicProjection, true);
	bluRayShader->setInt("uTexture", 0, true);

	backgroundShader->setMatrix4f("uProjection", orthographicProjection, true);
	backgroundShader->setVector2f("uResolution", glm::vec2(this->width, this->height), true);

	laserShader->setMatrix4f("uProjection", orthographicProjection, true);
	laserShader->setInt("uTexture", 0, true);

	dotShader->setMatrix4f("uProjection", orthographicProjection, true);
	dotShader->setVector4f("uColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true);
	
	Texture2D* dvdTexture = ResourceManager::getInstance()->addTexture2D(workingDirectory + "\\assets\\textures\\dvdLogo.png", true, "dvdTexture");
	Texture2D* bluRayTexture = ResourceManager::getInstance()->addTexture2D(workingDirectory + "\\assets\\textures\\bluRayLogo.png", true, "bluRayTexture");
	Texture2D* laserTexture = ResourceManager::getInstance()->addTexture2D(workingDirectory + "\\assets\\textures\\laser.png", true, "laserTexture");

	ResourceManager::getInstance()->addDrawData("projectileDrawData", *projectileMesh, *projectileShader, *laserTexture);
	ResourceManager::getInstance()->addDrawData("bluRayDrawData", *bluRayMesh, *bluRayShader, *bluRayTexture);
	ResourceManager::getInstance()->addDrawData("dotDrawData", *dotMesh, *dotShader, *dvdTexture);

	GameObjectManager::getInstance()->addGameObject("laserGameObject", "laser", * laserMesh, *laserShader, *laserTexture, 9999.0f, 9999.0f, 20.0f, 15.0f, 1.0f, 0.0f, 0.0f, 450.0f, false);
	GameObjectManager::getInstance()->addGameObject("dvdGameObject", "dvd", *dvdMesh, *dvdShader, *dvdTexture, this->width / 2, this->height / 2, 160.0f , 120.0f, 1.0f, 0.0f, 200.0f, 200.0f, false);
	GameObjectManager::getInstance()->addGameObject("backgroundGameObject", "background", *backgroundMesh, *backgroundShader, *dvdTexture, this->width / 2, this->height / 2, this->width, this->height, 1.0f, 0.0f, 0.0f, 0.0f, false);
}
void Game::start() {
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
			dvdGameObject->setPositionX(this->width / 2);
			dvdGameObject->setPositionY(this->height / 2);
		}
	}
	if (this->gameState == LOSS) {
		if (this->keys[GLFW_KEY_R]) {
			std::cout << "Pressed R" << std::endl;
			this->gameState = SCREEN_SAVER;
			ResourceManager::getInstance()->clear(true);
			GameObjectManager::getInstance()->clear(true);
			start();
		}
	}
}
void Game::update(float dt) {
	GameObject* dvdGameObject = GameObjectManager::getInstance()->getGameObjectByName("dvdGameObject");
	GameObject* backgroundGameObject = GameObjectManager::getInstance()->getGameObjectByName("backgroundGameObject");
	GameObject* laserGameObject = GameObjectManager::getInstance()->getGameObjectByName("laserGameObject");
	std::vector<GameObject*>* enemies = GameObjectManager::getInstance()->getGameObjectsByTag("enemy");
	backgroundGameObject->getDrawData()->getShader()->setFloat("uTime", glfwGetTime(), true);
	dvdGameObject->getDrawData()->getShader()->setFloat("uTime", glfwGetTime(), true);
	
	Renderer::getInstance()->colorBackground(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Renderer::getInstance()->drawUntextured(*backgroundGameObject, true);
	if (this->gameState == SCREEN_SAVER) {
		int colorIndex = 0;
		glm::vec4 dvdColor = glm::vec4(1.0f);
		dvdGameObject->setPositionX(dvdGameObject->getPositionX() + dvdGameObject->getSpeedX() * dt);
		dvdGameObject->setPositionY(dvdGameObject->getPositionY() + dvdGameObject->getSpeedY() * dt);
		if (dvdGameObject->getPositionX() + dvdGameObject->getScaledSizeX() / 2.0f >= this->width) {
			colorIndex = rand() % 8;
			dvdColor = this->colorsArray[colorIndex];
			dvdGameObject->getDrawData()->getShader()->setVector4f("uColor", dvdColor, true);

			dvdGameObject->setPositionX(this->width - (dvdGameObject->getScaledSizeX() / 2.0f));
			dvdGameObject->setSpeedX(-dvdGameObject->getSpeedX());
		}
		else if (dvdGameObject->getPositionX() - (dvdGameObject->getScaledSizeX() / 2.0f) <= 0.0f) {
			colorIndex = rand() % 8;
			dvdColor = this->colorsArray[colorIndex];
			dvdGameObject->getDrawData()->getShader()->setVector4f("uColor", dvdColor, true);

			dvdGameObject->setPositionX(0.0f + (dvdGameObject->getScaledSizeX() / 2.0f));
			dvdGameObject->setSpeedX(-dvdGameObject->getSpeedX());
		}
		if (dvdGameObject->getPositionY() + (dvdGameObject->getScaledSizeY() / 2.0f) >= this->height) {
			colorIndex = rand() % 8;
			dvdColor = this->colorsArray[colorIndex];
			dvdGameObject->getDrawData()->getShader()->setVector4f("uColor", dvdColor, true);

			dvdGameObject->setPositionY(this->height - (dvdGameObject->getScaledSizeY() / 2.0f));
			dvdGameObject->setSpeedY(-dvdGameObject->getSpeedY());
		}
		else if (dvdGameObject->getPositionY() - (dvdGameObject->getScaledSizeY() / 2.0f) <= 0.0f) {
			colorIndex = rand() % 8;
			dvdColor = this->colorsArray[colorIndex];
			dvdGameObject->getDrawData()->getShader()->setVector4f("uColor", dvdColor, true);

			dvdGameObject->setPositionY(0.0f + (dvdGameObject->getScaledSizeY() / 2.0f));
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
			dvdGameObject->getDrawData()->getShader()->setVector4f("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true);
			spawnEnemies(this->numberOfLines, this->numberOfEnemiesPerLine);
		}
	}
	else if (this->gameState == ACTIVE) {
		updateEnemies(dt);
		trimEnemyProjectiles(dt);
		spawnEnemyProjectiles(dt);
		updateEnemyProjectiles(dt);		
		Renderer::getInstance()->draw(*dvdGameObject, true);
		updateLaser(*laserGameObject, *dvdGameObject, dt);
		checkCollisions(dt);
		if (dvdGameObject->getIsHit()) {
			this->dvdDestructionDuration -= dt;
			if (this->dvdDestructionDuration < 0) {
				this->gameState = LOSS;
				dvdGameObject->getDrawData()->getShader()->setBool("uDestroyed", false, true);
			}
		}
		if (this->score == enemies->size()) {
			this->gameState = WIN;
			this->windowTitle = "Win!";
			glfwSetWindowTitle(this->window, this->windowTitle.c_str());
			this->dvdDestinationX = this->width / 2;
			this->dvdDestinationY = this->height / 2;
			this->deltaX = this->dvdDestinationX - dvdGameObject->getPositionX();
			this->deltaY = this->dvdDestinationY - dvdGameObject->getPositionY();
			this->deltaVector = glm::sqrt(this->deltaX * this->deltaX + this->deltaY * this->deltaY);
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
			ResourceManager::getInstance()->clear(true);
			GameObjectManager::getInstance()->clear(true);
			start();
		}
	}
	else if (this->gameState == LOSS) {
		this->windowTitle = "Game Over, Press 'R' To Restart Game";
		glfwSetWindowTitle(this->window, this->windowTitle.c_str());
		float currentInfinityPositionX = this->infinityPositions->at(this->currentInfinityPosition % this->infinityPositionsCount)->x;
		float currentInfinityPositionY = this->infinityPositions->at(this->currentInfinityPosition % this->infinityPositionsCount)->y;
		dvdGameObject->setPositionX(currentInfinityPositionX);
		dvdGameObject->setPositionY(currentInfinityPositionY);
		Renderer::getInstance()->draw(*dvdGameObject, true);
		this->currentInfinityPosition++;
	}
	delete enemies;
}
void Game::clear() {
	delete[] this->keys;
	delete[] this->colorsArray;
	delete[] this->intervals;
	delete this->soundEngine;
}
void Game::updateLaser(GameObject& laserGameObject, GameObject& dvdGameObject, float dt) {
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
		laserGameObject.setPositionY(dvdGameObject.getPositionY() + (dvdGameObject.getScaledSizeY()) / 2 + 20.0f);
	}
}
void Game::spawnEnemies(int numberOfLines, int numberOfEnemiesPerLine) {
	DrawData* bluRayDrawData = ResourceManager::getInstance()->getDrawDataByName("bluRayDrawData");
	float section = (float)this->width / numberOfEnemiesPerLine;

	float percentOfSizeX = 0.5f;
	float percentOfGapX = 0.25f;
	float remainingPercentage = 1 - percentOfSizeX - (percentOfGapX * 2);

	float bluRaySizeX = section * percentOfSizeX;
	float bluRaySizeY = bluRaySizeX * 0.75f;

	float gapSizeX = section * percentOfGapX;
	float gapSizeY = bluRaySizeY * 0.25f;

	float distanceX = bluRaySizeX + (gapSizeX * 2);
	float distanceY = bluRaySizeY + (gapSizeY * 2);

	float emptySpaceInGap = (section * remainingPercentage) / 2.0f;
	float initialEnemyX = (bluRaySizeX / 2.0f) + gapSizeX + emptySpaceInGap;
	float currentEnemyX = initialEnemyX;
	float currentEnemyY = this->height - (bluRaySizeY / 2.0f) - gapSizeY;

	for (int i = 0; i < numberOfLines; i++) {
		for (int j = 0; j < numberOfEnemiesPerLine; j++) {
			GameObjectManager::getInstance()->addGameObject("enemy" + std::to_string(i * numberOfEnemiesPerLine + j), "enemy", *bluRayDrawData, currentEnemyX, currentEnemyY, bluRaySizeX, bluRaySizeY, 1.0f, 0.0f, 0.0f, 10.0f, false);
			currentEnemyX += distanceX + (emptySpaceInGap * 2);
		}
		currentEnemyX = initialEnemyX;
		currentEnemyY -= distanceY;
	}
}
void Game::updateEnemies(float dt) {
	std::vector<GameObject*>* enemies = GameObjectManager::getInstance()->getGameObjectsByTag("enemy");
	for (int i = 0; i < enemies->size(); i++) {
		enemies->at(i)->setPositionY(enemies->at(i)->getPositionY() - enemies->at(i)->getSpeedY() * dt);
		enemies->at(i)->getDrawData()->getShader()->setVector4f("uColor", glm::vec4(0.125f, 0.4f, 0.95f, 1.0f), true);
		Renderer::getInstance()->draw(*enemies->at(i), false);
	}
	delete enemies;
}

void Game::trimEnemies(){
	std::vector<GameObject*>* enemies = GameObjectManager::getInstance()->getGameObjectsByTag("enemy");
	for (int i = 0; i < enemies->size(); i++) {
		if (enemies->at(i)->getIsHit()) {
			GameObjectManager::getInstance()->removeGameObject(enemies->at(i));
		}
	}
	delete enemies;
}

void Game::checkCollisions(float dt) {
	std::vector<GameObject*>* enemies = GameObjectManager::getInstance()->getGameObjectsByTag("enemy");
	std::vector<GameObject*>* projectiles = GameObjectManager::getInstance()->getGameObjectsByTag("projectile");
	bool foundCollision = false;
	GameObject* dvdGameObject = GameObjectManager::getInstance()->getGameObjectByName("dvdGameObject");
	GameObject* laserGameObject = GameObjectManager::getInstance()->getGameObjectByName("laserGameObject");
	for (int i = 0; i < enemies->size(); i++) {
		/*bool collisionX = enemies->at(i)->getPositionX() + (enemies->at(i)->getScaledSizeX() / 2.0f) >= laserGameObject->getPositionX() - (laserGameObject->getScaledSizeX() / 2.0f) && laserGameObject->getPositionX() - (laserGameObject->getScaledSizeX() / 2.0f) <= enemies->at(i)->getPositionX() + (laserGameObject->getScaledSizeX() / 2.0f);
		bool collisionY = enemies->at(i)->getPositionY() - (enemies->at(i)->getScaledSizeY() / 2.0f) <= laserGameObject->getPositionY() + (laserGameObject->getScaledSizeY() / 2.0f) && laserGameObject->getPositionY() + (laserGameObject->getScaledSizeY() / 2.0f) >= enemies->at(i)->getPositionY() - (laserGameObject->getScaledSizeY() / 2.0f);*/
		bool collisionX = enemies->at(i)->getPositionX() + enemies->at(i)->getScaledSizeX() >= laserGameObject->getPositionX() && laserGameObject->getPositionX() + laserGameObject->getScaledSizeX() >= enemies->at(i)->getPositionX();
		bool collisionY = enemies->at(i)->getPositionY() + enemies->at(i)->getScaledSizeY() >= laserGameObject->getPositionY() && laserGameObject->getPositionY() + laserGameObject->getScaledSizeY() >= enemies->at(i)->getPositionY();
		if (collisionX && collisionY) {
			this->soundEngine->setSoundVolume(1.0f);
			this->soundEngine->play2D("assets\\sounds\\bleep.wav", false);
			enemies->at(i)->setIsHit(true);
			enemies->at(i)->setPositionX(9999.0f);
			enemies->at(i)->setPositionY(9999.0f);
			this->score++;
			this->windowTitle = "Score: " + std::to_string(this->score);
			glfwSetWindowTitle(this->window, this->windowTitle.c_str());
			this->laserIsShooting = false;
		}
		if (enemies->at(i)->getPositionY() - (enemies->at(i)->getScaledSizeY() / 2.0f) <= 0) {
			this->gameState = LOSS;
			return;
		}
	}
	if (projectiles->size() > 0) {
		for (int i = 0; i < projectiles->size(); i++) {
			/*bool collisionX = projectiles->at(i)->getPositionX() + (projectiles->at(i)->getScaledSizeX() / 2.0f) >= dvdGameObject->getPositionX() - (dvdGameObject->getScaledSizeX() / 2.0f) && dvdGameObject->getPositionX() - (dvdGameObject->getScaledSizeX() / 2.0f) <= projectiles->at(i)->getPositionX() + (dvdGameObject->getScaledSizeX() / 2.0f);
			bool collisionY = projectiles->at(i)->getPositionY() - (projectiles->at(i)->getScaledSizeY() / 2.0f) <= dvdGameObject->getPositionY() + (dvdGameObject->getScaledSizeY() / 2.0f) && dvdGameObject->getPositionY() + (dvdGameObject->getScaledSizeY() / 2.0f) >= projectiles->at(i)->getPositionY() - (dvdGameObject->getScaledSizeY() / 2.0f);*/
			bool collisionX = projectiles->at(i)->getPositionX() + projectiles->at(i)->getScaledSizeX() >= dvdGameObject->getPositionX() && dvdGameObject->getPositionX() + dvdGameObject->getScaledSizeX() >= projectiles->at(i)->getPositionX();
			bool collisionY = projectiles->at(i)->getPositionY() + projectiles->at(i)->getScaledSizeY() >= dvdGameObject->getPositionY() && dvdGameObject->getPositionY() + dvdGameObject->getScaledSizeY() >= projectiles->at(i)->getPositionY();
			if (collisionX && collisionY) {
				this->soundEngine->setSoundVolume(0.1f);
				this->soundEngine->play2D("assets\\sounds\\lose.wav", false);
				dvdGameObject->setIsHit(true);
				dvdGameObject->getDrawData()->getShader()->setFloat("uStartTime", glfwGetTime(), true);
				dvdGameObject->getDrawData()->getShader()->setBool("uDestroyed", true, true);
				GameObjectManager::getInstance()->removeGameObject(projectiles->at(i));
			}
		}
	}
	delete enemies;
	delete projectiles;
}

void Game::spawnEnemyProjectiles(float dt){
	std::vector<GameObject*>* enemies = GameObjectManager::getInstance()->getGameObjectsByTag("enemy");
	this->interval -= dt;
	if (this->interval < 0) {
		this->enemyIndexOfProjectile = rand() % enemies->size();
		GameObject* bluRayGameObject = enemies->at(this->enemyIndexOfProjectile);
		DrawData* projectileDrawData = ResourceManager::getInstance()->getDrawDataByName("projectileDrawData");
		GameObject* projectileGameObject = GameObjectManager::getInstance()->addGameObject("projectileGameObject", "projectile", *projectileDrawData, bluRayGameObject->getPositionX(), bluRayGameObject->getPositionY() - bluRayGameObject->getScaledSizeY() / 2 - 20.0f,
			25.0f, 25.0f, 1.0f, 0.0f, 0.0f, 300.0f, false);
		this->interval = this->intervals[rand() & 4];
	}
	delete enemies;
}
void Game::trimEnemyProjectiles(float dt) {
	std::vector<GameObject*>* projectiles = GameObjectManager::getInstance()->getGameObjectsByTag("projectile");
	for (int i = 0; i < projectiles->size(); i++) {
		if (projectiles->at(i)->getPositionX() + (projectiles->at(i)->getScaledSizeX() / 2) >= this->width - 0.0f ||
			projectiles->at(i)->getPositionX() - (projectiles->at(i)->getScaledSizeX() / 2) <= 0.0f ||
			projectiles->at(i)->getPositionY() + (projectiles->at(i)->getScaledSizeY() / 2) >= this->height - 0.0f ||
			projectiles->at(i)->getPositionY() - (projectiles->at(i)->getScaledSizeY() / 2) <= 0.0f) {
			GameObjectManager::getInstance()->removeGameObject(projectiles->at(i));
		}
	}
	delete projectiles;
}
void Game::updateEnemyProjectiles(float dt) {
	std::vector<GameObject*>* projectiles = GameObjectManager::getInstance()->getGameObjectsByTag("projectile");
	if (projectiles->size() > 0) {
		for (int i = 0; i < projectiles->size(); i++) {
			projectiles->at(i)->setPositionY(projectiles->at(i)->getPositionY() - projectiles->at(i)->getSpeedY() * dt);
			projectiles->at(i)->setRotation(projectiles->at(i)->getRotation() + 3500.0f * dt);
			projectiles->at(i)->getDrawData()->getShader()->setFloat("uTime", glfwGetTime(), true);
			Renderer::getInstance()->drawUntextured(*projectiles->at(i), true);
		}
	}
	delete projectiles;
}
void Game::addDots(float dt){
	DrawData* dotDrawData = ResourceManager::getInstance()->getDrawDataByName("dotDrawData");
	GameObject* dvdGameObject = GameObjectManager::getInstance()->getGameObjectByName("dvdGameObject");
	for (int i = 0; i < this->infinityPositionsCount; i++) {
		float currentPositionX = ((glm::cos(t) + 1.0f) / 2.0f) * this->width;
		float currentPositionY = ((glm::sin(t) * glm::cos(t) + 1.0f) / 2.0f) * this->height;
		this->infinityPositions->push_back(new glm::vec2(currentPositionX, currentPositionY));
		float speed = 0.016f;
		if (this->t > this->upperBound) {
			this->t = this->upperBound;
			speed = -speed;
		}
		if (this->t < this->lowerBound) {
			this->t = this->lowerBound;
			speed = -speed;
		}
		this->t += speed;
	}
}