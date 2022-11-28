#pragma once

#include "GLData.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Texture2D.hpp"

class Mesh {
private:
	std::string name;
	VertexArray* vertexArray;
	VertexBuffer* vertexBuffer;
	unsigned int textureChannel;
	Texture2D* texture2D;
	float* data;
	unsigned int* indices;
	unsigned int vertexCount;
public:
	Mesh();
	Mesh(float* data, unsigned int dataSize, unsigned int* indices, unsigned int indicesSize, std::string name, int positionAttributeNumber, int positionDimensions, int colorAttributeNumber, int colorDimensions, int textureAttributeNumber, int textureDimensions, const Texture2D& texture2D, unsigned int textureChannel);
	~Mesh();
	/*float* copyFloatArray(float* source, unsigned int sourceSize);
	unsigned int* copyUnsignedIntArray(unsigned int* source, unsigned int sourceSize);*/
	std::string getName() {
		return this->name;
	}
	VertexArray* getVertexArray() {
		return this->vertexArray;
	}
	VertexBuffer* getVertexBuffer() {
		return this->vertexBuffer;
	}
	unsigned int getTextureChannel() {
		return this->textureChannel;
	}
	Texture2D* getTexture2D() {
		return this->texture2D;
	}
	float* getData() {
		return this->data;
	}
	unsigned int* getIndices() {
		return this->indices;
	}
	unsigned int getVertexCount() {
		return this->vertexCount;
	}
};