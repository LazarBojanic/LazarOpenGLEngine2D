#pragma once

#include "Primitive.hpp"

class Quad : public Primitive {
public:
	Quad(boolean indexed) {
		this->indexed = indexed;
		if (this->indexed) {
			this->data = new float[32] {
		   //positions             colors               texture coordinates
			-0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f, //bottom left
			 0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f, //bottom right
			 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f, //top right
			-0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f,	0.0f, 1.0f  //top left
			};
			this->dataCount = 32;
			this->dataSize = 32 * sizeof(float);
			this->indices = new unsigned int[6] {
				0, 1, 2,
				2, 3, 0
			};
			this->indicesCount = 6;
			this->indicesSize = 6 * sizeof(unsigned int);
		}
		else {
			this->data = new float[48] {
		   //positions             colors               texture coordinates
			-0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f, //bottom left
			 0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f, //bottom right
			 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f, //top right
			 0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f, //bottom right
			 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f, //top right
			-0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f,	0.0f, 1.0f  //top left
			};
			this->dataCount = 48;
			this->dataSize = 48 * sizeof(float);
			this->indices = nullptr;
			this->indicesCount = 0;
			this->indicesSize = 0;
		}
	}
};