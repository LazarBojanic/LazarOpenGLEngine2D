#pragma once

#include "Primitive.hpp"

class Triangle : public Primitive {
public:
	Triangle() {
		this->vertexPositionsAndColorsAndTextureCoordinates = new float[24] {
			  //positions             colors                 texture coordinates
			   -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f, //bottom left
				0.0f,  0.5f, 0.0f,	  0.0f, 1.0f, 0.0f,	   0.5f, 1.0f, //top middle
				0.5f, -0.5f, 0.0f,	  0.0f, 0.0f, 1.0f,	   1.0f, 0.0f  //bottom right
		};
		this->indices = new unsigned int[3] {
			0, 1, 2
		};
	}
	float* getVertexPositionsAndColorsAndTextureCoordinates() {
		return this->vertexPositionsAndColorsAndTextureCoordinates;
	}
	unsigned int* getIndices() {
		return this->indices;
	}
};