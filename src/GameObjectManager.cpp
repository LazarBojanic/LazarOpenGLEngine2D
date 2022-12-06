#include "GameObjectManager.hpp"

GameObjectManager* GameObjectManager::instance;

GameObjectManager::GameObjectManager() {
    this->gameObjectList = new std::vector<GameObject*>();
}

GameObjectManager::~GameObjectManager() {
    delete this->gameObjectList;
}

GameObjectManager* GameObjectManager::getInstance() {
    if (!instance) {
        instance = new GameObjectManager();
    }
    return instance;
}

GameObject* GameObjectManager::addGameObject(std::string name, Mesh& mesh, Shader& shader, Texture2D& texture2D,
    float positionX, float positionY, float sizeX, float sizeY, float scale, float rotation, float speedX, float speedY, bool isHit){
    DrawData* drawData = new DrawData(mesh, shader, texture2D);
    GameObject* gameObject = new GameObject(name, *drawData, positionX, positionY, sizeX, sizeY, scale, rotation, speedX, speedY, isHit);
    this->gameObjectList->push_back(gameObject);
    return gameObject;
}

GameObject* GameObjectManager::getGameObjectByName(std::string name) {
    for (int i = 0; i < this->gameObjectList->size(); i++) {
        if (this->gameObjectList->at(i)->getName() == name) {
            return this->gameObjectList->at(i);
        }
    }
}
void GameObjectManager::clear() {
    delete this->gameObjectList;
}