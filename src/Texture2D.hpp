#pragma once

#include "GLData.hpp"

class Texture2D{
private:
    std::string name;
	unsigned int textureID;
	unsigned int width;
	unsigned int height;
    unsigned int wrap_S;
    unsigned int wrap_T;
    unsigned int filterMin;
    unsigned int filterMax;
    unsigned int imageFormat;
public:
    Texture2D();
    //Texture2D(Texture2D* other);
    Texture2D(std::string textureFilePath, bool alpha, std::string name);
    ~Texture2D();
    void generate(unsigned char* data);
    void bind(unsigned int textureChannel);
    void unbind();

	std::string getName() {
		return this->name;
	}
	unsigned int getTextureID() {
		return this->textureID;
	}
	unsigned int getWidth() {
		return this->width;
	}
	unsigned int getHeight() {
		return this->height;
	}
	unsigned int getWrap_S() {
		return this->wrap_S;
	}
	unsigned int getWrap_T() {
		return this->wrap_T;
	}
	unsigned int getFilterMin() {
		return this->filterMin;
	}
	unsigned int getFilterMax() {
		return this->filterMax;
	}
	unsigned int getImageFormat() {
		return this->imageFormat;
	}
};

