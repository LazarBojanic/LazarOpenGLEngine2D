#pragma once

#include "GLData.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"

class DrawData {
private:
	Mesh* mesh;
	Shader* shader;
	Texture2D* texture2D;
public:
	DrawData(const Mesh& mesh, const Shader& shader, const Texture2D& texture2D);
	~DrawData();
	Mesh* getMesh() {
		return this->mesh;
	}
	Shader* getShader() {
		return this->shader;
	}
	Texture2D* getTexture2D() {
		return this->texture2D;
	}
	void setShader(const Shader& shader);
};