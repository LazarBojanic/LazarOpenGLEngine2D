#pragma once


#include "GLData.hpp"
#include "ResourceManager.hpp"
#include "GameObjectManager.hpp"
#include "Renderer.hpp"
#include "Triangle.hpp"
#include "Quad.hpp"
#include "Entity.hpp"

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
    std::string windowTitle;
    static Game* instance;
    GameState gameState;
    bool* keys;
    int keysSize = 1024;
    unsigned int width, height;

    float dvdWidth, dvdHeight;
    float dvdX, dvdY;
    float dvdXSpeed, dvdYSpeed;
    float dvdGameSpeed;

    float dvdRotationWhileTransition;
    float dvdRotationWhileTransitionSpeed;
    float dvdScaleWhileTransition;
    float destinationScale;
    float deltaScale;

    float bluRayWidth, bluRayHeight;
    float bluRayX, bluRayY;
    float bluRayXSpeed, bluRayYSpeed;

    float deltaX;
    float deltaY;
    float deltaVector;

    float dvdDestinationX;
    float dvdDestinationY;
    float dvdTransitionSpeed;

    int numberOfLines;
    int numberOfEnemiesPerLine;
    std::vector<glm::vec2>* enemyPositions;
    std::vector<Entity*>* enemies;

    float laserX, laserY;
    float laserWidth, laserHeight;
    float laserSpeedY;
    bool laserIsShooting;

    int score;

    glm::vec4* colorsArray;
    int colorsArrayCount = 8;
    
public:
    Game(GLFWwindow* window, unsigned int width, unsigned int height);
    ~Game();
    static Game* getInstance(GLFWwindow* window, unsigned int width, unsigned int height);
    static Game* getInstance();
    void init();
    void initResources();
    void initVariables();
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
    void updateEnemies(GameObject& gameObject);
    void updateWindowSize(int width, int height);
    bool checkCollision(Entity& entity, glm::vec2 positionTwo, glm::vec2 sizeTwo);
};
    