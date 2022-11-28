#pragma once

#include "GLData.hpp"
#include "GameObject.hpp"

class GameObjectManager{
private:
	GameObjectManager();
	~GameObjectManager();
	static GameObjectManager* instance;

	std::vector<GameObject*>* gameObjectList;


public:
	static GameObjectManager* getInstance();
	void addGameObject(GameObject& gameObject);
	GameObject* getGameObjectByName(std::string name);
};

