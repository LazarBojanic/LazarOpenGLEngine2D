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

    glm::vec4* colorsArray = new glm::vec4[8]{
        glm::vec4(0.7f, 0.4f, 0.4f, 1.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(0.4f, 0.4f, 0.7f, 1.0f),
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
        glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec4(0.75f, 0.0f, 0.75f, 1.0f)
    };
    int colorsArrayCount = 8;
    
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
    void initKeys();
    void spawnEnemies(int numberOfLines, int numberOfEnemiesPerLine);
    void updateWindowSize(int width, int height);
};
    