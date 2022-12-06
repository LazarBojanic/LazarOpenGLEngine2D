#include "ResourceManager.hpp"

ResourceManager* ResourceManager::instance;

ResourceManager::ResourceManager() {
    this->meshList = new std::vector<Mesh*>();
    this->shaderList = new std::vector<Shader*>();
    this->texture2DList = new std::vector<Texture2D*>();
}
ResourceManager::~ResourceManager() {
    delete this->meshList;
    delete this->shaderList;
    delete this->texture2DList;
}
ResourceManager* ResourceManager::getInstance() {
    if (!instance) {
        instance = new ResourceManager();
    }
    return instance;
}

Mesh* ResourceManager::addMesh(Primitive& primitive, std::string name, int positionAttributeNumber, int positionDimensions, int colorAttributeNumber, int colorDimensions, int textureAttributeNumber, int textureDimensions){
    Mesh* mesh = new Mesh(primitive, name, positionAttributeNumber, positionDimensions, colorAttributeNumber, colorDimensions, textureAttributeNumber, textureDimensions);
    if (std::find(this->meshList->begin(), this->meshList->end(), mesh) == this->meshList->end()) {
        this->meshList->push_back(mesh);
    }
    return mesh;
}

Shader* ResourceManager::addShader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string name){
    Shader* shader = new Shader(vertexShaderPath, fragmentShaderPath, name);
    if (std::find(this->shaderList->begin(), this->shaderList->end(), shader) == this->shaderList->end()) {
        this->shaderList->push_back(shader);
    }
    return shader;
}

Texture2D* ResourceManager::addTexture2D(std::string texture2DPath, bool alpha, std::string name){
    Texture2D* texture2D = new Texture2D(texture2DPath, alpha, name);
    if (std::find(this->texture2DList->begin(), this->texture2DList->end(), texture2D) == this->texture2DList->end()) {
        this->texture2DList->push_back(texture2D);
    }
    return texture2D;
}

Mesh* ResourceManager::getMeshByName(std::string name){
    for (int i = 0; i < this->meshList->size(); i++) {
        if (this->meshList->at(i)->getName() == name) {
            return this->meshList->at(i);
        }
    }
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
void ResourceManager::clear() {
    delete this->meshList;
    delete this->shaderList;
    delete this->texture2DList;
}