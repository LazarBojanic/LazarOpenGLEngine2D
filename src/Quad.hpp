#pragma once

#include "Primitive.hpp"

class Quad : public Primitive {
public:
	Quad() {
		this->vertexPositionsAndColorsAndTextureCoordinates = new float[32] {
		   //positions             colors               texture coordinates
			-0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f, //bottom left
			 0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f, //bottom right
			 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f, //top right
			-0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f,	0.0f, 1.0f  //top left
		};
		this->indices = new unsigned int[6] {
			0, 1, 2,
			2, 3, 0
		};	
	}
	float* getVertexPositionsAndColorsAndTextureCoordinates() {
		return this->vertexPositionsAndColorsAndTextureCoordinates;
	}
	unsigned int* getIndices() {
		return this->indices;
	}
};