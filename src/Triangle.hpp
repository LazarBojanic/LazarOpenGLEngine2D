#pragma once

#include "Primitive.hpp"

class Triangle : public Primitive {
public:
	Triangle(bool indexed) {
		this->indexed = indexed;
		if (this->indexed) {
			this->data = new float[24] {
				  //positions             colors               texture coordinates
				   -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f, //bottom left
					0.0f,  0.5f, 0.0f,	  0.0f, 1.0f, 0.0f,	   0.5f, 1.0f, //top middle
					0.5f, -0.5f, 0.0f,	  0.0f, 0.0f, 1.0f,	   1.0f, 0.0f  //bottom right
			};
			this->dataCount = 24;
			this->dataSize = 24 * sizeof(float);
			this->indices = new unsigned int[3] {
				0, 1, 2
			};
			this->indicesCount = 3;
			this->indicesSize = 3 * sizeof(unsigned int);
		}
		else {
			this->data = new float[24] {
				  //positions             colors               texture coordinates
				   -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f, //bottom left
					0.0f,  0.5f, 0.0f,	  0.0f, 1.0f, 0.0f,	   0.5f, 1.0f, //top middle
					0.5f, -0.5f, 0.0f,	  0.0f, 0.0f, 1.0f,	   1.0f, 0.0f  //bottom right
			};
			this->dataCount = 24;
			this->dataSize = 24 * sizeof(float);
			this->indices = nullptr;
			this->indicesCount = 0;
			this->indicesSize = 0;
		}
	}
};