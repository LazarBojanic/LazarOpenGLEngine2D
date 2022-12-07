#pragma once

#include "GLData.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"
#include "GameObject.hpp"

class GameObjectManager{
private:
	GameObjectManager();
	~GameObjectManager();
	static GameObjectManager* instance;
	std::vector<GameObject*>* gameObjectList;
public:
	static GameObjectManager* getInstance();
	GameObject* addGameObject(GameObject* gameObject);
	GameObject* addGameObject(std::string name, std::string tag, DrawData& drawData,
		float positionX, float positionY, float sizeX, float sizeY, float scale, float rotation, float speedX, float speedY, bool isHit);
	GameObject* addGameObject(std::string name, std::string tag, Mesh& mesh, Shader& shader, Texture2D& texture2D,
		float positionX, float positionY, float sizeX, float sizeY, float scale, float rotation, float speedX, float speedY, bool isHit);
	GameObject* getGameObjectByName(std::string name);
	GameObject* getGameObjectByTag(std::string tag);
	std::vector<GameObject*>* getGameObjectsByTag(std::string tag);
	void removeGameObject(GameObject* gameObject);
	void clear(bool reinitialize);
};

