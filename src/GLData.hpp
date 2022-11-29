#pragma once

#define MIN_RAND 100
#define MAX_RAND 256

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLData {
public:
	static float* copyFloatArray(float* source, unsigned int sourceSize) {
		float* result = new float[sourceSize];
		for (unsigned int i = 0; i < sourceSize; i++) {
			result[i] = source[i];
		}
		return result;
	}
	static unsigned int* copyUnsignedIntArray(unsigned int* source, unsigned int sourceSize) {
		unsigned int* result = new unsigned int[sourceSize];
		for (unsigned int i = 0; i < sourceSize; i++) {
			result[i] = source[i];
		}
		return result;
	}
};