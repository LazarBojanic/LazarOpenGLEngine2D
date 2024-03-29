#pragma once

#include "Util.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Texture2D.hpp"
#include "Primitive.hpp"

class Mesh {
private:
	GUID id;
	std::string name;
	VertexArray* vertexArray;
	VertexBuffer* vertexBuffer;
	Primitive* primitive;
	unsigned int textureChannel;
public:
	Mesh();
	Mesh(Primitive& primitive, std::string name, int positionAttributeNumber, int positionDimensions, int colorAttributeNumber, int colorDimensions, int textureAttributeNumber, int textureDimensions);
	~Mesh();
	inline GUID getId() {
		return this->id;
	}
	inline std::string getName() {
		return this->name;
	}
	inline VertexArray* getVertexArray() {
		return this->vertexArray;
	}
	inline VertexBuffer* getVertexBuffer() {
		return this->vertexBuffer;
	}
	inline Primitive* getPrimitive() {
		return this->primitive;
	}
	inline unsigned int getTextureChannel() {
		return this->textureChannel;
	}
};