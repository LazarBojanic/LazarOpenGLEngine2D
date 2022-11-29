#include "ResourceManager.hpp"

ResourceManager* ResourceManager::instance;

ResourceManager::ResourceManager() {
    this->shaderList = new std::vector<Shader*>();
    this->texture2DList = new std::vector<Texture2D*>();
}
ResourceManager::~ResourceManager() {
    delete this->shaderList;
    delete this->texture2DList;
}
ResourceManager* ResourceManager::getInstance() {
    if (!instance) {
        instance = new ResourceManager();
    }
    return instance;
}

Shader* ResourceManager::addShader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string name){
    Shader* shader = new Shader(vertexShaderPath, fragmentShaderPath, name);
    //std::vector<Shader*> tempList = *this->shaderList;
    if (std::find(this->shaderList->begin(), this->shaderList->end(), shader) == this->shaderList->end()) {
        this->shaderList->push_back(shader);
    }
    /*for (int i = 0; i < this->shaderList->size(); i++) {
        if (this->shaderList->at(i)->getName() != name) {
            this->shaderList->push_back(shader);
        }
    }*/
    return shader;
}

Texture2D* ResourceManager::addTexture2D(std::string texture2DPath, bool alpha, std::string name){
    Texture2D* texture2D = new Texture2D(texture2DPath, alpha, name);
    if (std::find(this->texture2DList->begin(), this->texture2DList->end(), texture2D) == this->texture2DList->end()) {
        this->texture2DList->push_back(texture2D);
    }
    /*for (int i = 0; i < this->texture2DList->size() + 1; i++) {
        if (this->texture2DList->at(i)->getName() != name) {
            this->texture2DList->push_back(texture2D);
        }
    }*/
    return texture2D;
}

Shader* ResourceManager::getShaderByName(std::string name){
    for (int i = 0; i < this->shaderList->size(); i++) {
        if (this->shaderList->at(i)->getName() == name) {
            return this->shaderList->at(i);
        }
    }
    
}
Texture2D* ResourceManager::getTexture2DByName(std::string name) {
    for (int i = 0; i < this->texture2DList->size(); i++) {
        if (this->texture2DList->at(i)->getName() == name) {
            return this->texture2DList->at(i);
        }
    }
}
