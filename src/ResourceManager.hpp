#pragma once

#include "GLData.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"

class ResourceManager{
private:
	ResourceManager();
	~ResourceManager();
	static ResourceManager* instance;

	std::vector<Shader*>* shaderList;
	std::vector<Texture2D*>* texture2DList;

public:
	static ResourceManager* getInstance();
	
	Shader* addShader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string name);
	Texture2D* addTexture2D(std::string texture2DPath, bool alpha, std::string name);

	Shader* getShaderByName(std::string name);
	Texture2D* getTexture2DByName(std::string name);

	std::vector<Shader*>* getShaderList() {
		return this->shaderList;
	}
	std::vector<Texture2D*>* getTexture2DList() {
		return this->texture2DList;
	}
};