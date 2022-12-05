#include "GameObject.hpp"


GameObject::GameObject(std::string name, const Mesh& mesh, const Shader& shader, const Texture2D& texture2D) {
	this->name = name;
	this->mesh = new Mesh(mesh);
	this->shader = new Shader(shader);
	this->texture2D = new Texture2D(texture2D);
}
GameObject::~GameObject() {
	delete this->mesh;
	delete this->shader;
	delete this->texture2D;
}

void GameObject::setShader(const Shader& shader){
	this->shader = new Shader(shader);
}
