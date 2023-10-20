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

#include <windows.h>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <irrKlang/irrKlang.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define PI 3.141592

class Util {
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
	static std::string listToString(std::vector<glm::vec2>* list) {
		std::string result = "";
		for (int i = 0; i < list->size(); i++) {
			result += "Enemy X:" + std::to_string(list->at(i).x) + "Enemy Y:" + std::to_string(list->at(i).y) + "\n";
		}
		return result;
	}
	static std::string getDebugMeaning(GLenum number) {
    switch (number) {
		case GL_DEBUG_OUTPUT_SYNCHRONOUS:
			return "GL_DEBUG_OUTPUT_SYNCHRONOUS";
		case GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH:
			return "GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH";
		case GL_DEBUG_CALLBACK_FUNCTION:
			return "GL_DEBUG_CALLBACK_FUNCTION";
		case GL_DEBUG_CALLBACK_USER_PARAM:
			return "GL_DEBUG_CALLBACK_USER_PARAM";
		case GL_DEBUG_SOURCE_API:
			return "GL_DEBUG_SOURCE_API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			return "GL_DEBUG_SOURCE_SHADER_COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			return "GL_DEBUG_SOURCE_THIRD_PARTY";
		case GL_DEBUG_SOURCE_APPLICATION:
			return "GL_DEBUG_SOURCE_APPLICATION";
		case GL_DEBUG_SOURCE_OTHER:
			return "GL_DEBUG_SOURCE_OTHER";
		case GL_DEBUG_TYPE_ERROR:
			return "GL_DEBUG_TYPE_ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY:
			return "GL_DEBUG_TYPE_PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE:
			return "GL_DEBUG_TYPE_PERFORMANCE";
		case GL_DEBUG_TYPE_OTHER:
			return "GL_DEBUG_TYPE_OTHER";
		case GL_MAX_DEBUG_MESSAGE_LENGTH:
			return "GL_MAX_DEBUG_MESSAGE_LENGTH";
		case GL_MAX_DEBUG_LOGGED_MESSAGES:
			return "GL_MAX_DEBUG_LOGGED_MESSAGES";
		case GL_DEBUG_LOGGED_MESSAGES:
			return "GL_DEBUG_LOGGED_MESSAGES";
		case GL_DEBUG_SEVERITY_HIGH:
			return "GL_DEBUG_SEVERITY_HIGH";
		case GL_DEBUG_SEVERITY_MEDIUM:
			return "GL_DEBUG_SEVERITY_MEDIUM";
		case GL_DEBUG_SEVERITY_LOW:
			return "GL_DEBUG_SEVERITY_LOW";
		case GL_DEBUG_TYPE_MARKER:
			return "GL_DEBUG_TYPE_MARKER";
		case GL_DEBUG_TYPE_PUSH_GROUP:
			return "GL_DEBUG_TYPE_PUSH_GROUP";
		case GL_DEBUG_TYPE_POP_GROUP:
			return "GL_DEBUG_TYPE_POP_GROUP";
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			return "GL_DEBUG_SEVERITY_NOTIFICATION";
		case GL_MAX_DEBUG_GROUP_STACK_DEPTH:
			return "GL_MAX_DEBUG_GROUP_STACK_DEPTH";
		case GL_DEBUG_GROUP_STACK_DEPTH:
			return "GL_DEBUG_GROUP_STACK_DEPTH";
		}
	}
};