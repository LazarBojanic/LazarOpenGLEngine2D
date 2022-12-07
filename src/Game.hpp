#pragma once

#include "GLData.hpp"
#include "ResourceManager.hpp"
#include "GameObjectManager.hpp"
#include "Renderer.hpp"
#include "Triangle.hpp"
#include "Quad.hpp"

enum GameState {
    SCREEN_SAVER,
    TRANSITION_TO_ACTIVE,
    ACTIVE,
    WIN,
    LOSS
};

class Game {
private:
    GLFWwindow* window;
    ISoundEngine* soundEngine;
    std::string windowTitle;
    static Game* instance;
    GameState gameState;
    bool* keys;
    int keysSize = 1024;
    unsigned int width, height;
    double startTime;

    float dvdDestinationX;
    float dvdDestinationY;
    float dvdTransitionSpeed;

    float dvdRotationWhileTransition;
    float dvdRotationWhileTransitionSpeed;
    float dvdScaleWhileTransition;
    float destinationScale;
    float deltaScale;

    float deltaX;
    float deltaY;
    float deltaVector;

    int numberOfLines;
    int numberOfEnemiesPerLine;
    std::vector<GameObject*>* enemies;
    int enemyIndexOfProjectile;
    float* intervals;
    float interval;

    bool laserIsShooting;

    int score;

    glm::vec4* colorsArray;
    int colorsArrayCount = 8;
    
public:
    Game(GLFWwindow* window, unsigned int width, unsigned int height);
    ~Game();
    static Game* getInstance(GLFWwindow* window, unsigned int width, unsigned int height);
    static Game* getInstance();
    void initVariables();
    void initResources();
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
    void initKeys();
    void spawnEnemies(int numberOfLines, int numberOfEnemiesPerLine);
    void updateEnemies();
    void updateWindowSize(int width, int height);
    void checkCollisions();
    void updateLaser(GameObject& laserGameObject, GameObject& dvdGameObject, float dt);
    void spawnEnemyProjectiles(float dt);
    void updateEnemyProjectiles(float dt);
    void trimEnemyProjectiles(float dt);
};