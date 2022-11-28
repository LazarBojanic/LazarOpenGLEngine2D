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

void GameObjectManager::addGameObject(GameObject& gameObject) {
    this->gameObjectList->push_back(&gameObject);
}
GameObject* GameObjectManager::getGameObjectByName(std::string name) {
    for (int i = 0; i < this->gameObjectList->size(); i++) {
        if (this->gameObjectList->at(i)->getName() == name) {
            return this->gameObjectList->at(i);
        }
    }
}