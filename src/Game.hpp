#pragma once

#include "GLData.hpp"
#include "ResourceManager.hpp"
#include "GameObjectManager.hpp"
#include "Renderer.hpp"
#include "Triangle.hpp"
#include "Quad.hpp"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};


class Game {
private:
    static Game* instance;
    GameState gameState;
    bool* keys;
    unsigned int width, height;


    float x, y, xSpeed, ySpeed;
    
public:
    Game(unsigned int width, unsigned int height);
    ~Game();
    static Game* getInstance(unsigned int width, unsigned int height);
    static Game* getInstance();
    void init();
    void processInput(float dt);
    void update(float dt);
    void render(float dt);
    void clear();
    GameState getGameState() {
        return this->gameState;
    }
    bool* getKeys() {
        return this->keys;
    }
    unsigned int getWidth() {
        return this->width;
    }
    unsigned int getHeight() {
        return this->height;
    }
};
    