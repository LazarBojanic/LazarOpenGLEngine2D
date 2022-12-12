#include "Renderer.hpp"


Renderer* Renderer::instance;

Renderer::Renderer() {

}
Renderer::~Renderer() {
    
}

Renderer* Renderer::getInstance(){
    if (!instance) {
        instance = new Renderer();
    }
    return instance;
}

void Renderer::draw(GameObject& gameObject, bool scaled) {
    glm::mat4 modelView = glm::mat4(1.0f);
    modelView = glm::translate(modelView, glm::vec3(glm::vec2(gameObject.getPositionX(), gameObject.getPositionY()), 0.0f));
    modelView = glm::rotate(modelView, glm::radians(gameObject.getRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
    if (!scaled) {
        modelView = glm::scale(modelView, glm::vec3(glm::vec2(gameObject.getSizeX(), gameObject.getSizeY()), 1.0f));
    }
    else {
        modelView = glm::scale(modelView, glm::vec3(glm::vec2(gameObject.getScaledSizeX(), gameObject.getScaledSizeY()), 1.0f));
    }
    gameObject.getDrawData()->getMesh()->getVertexArray()->bind();
    gameObject.getDrawData()->getTexture2D()->bind(0);
    gameObject.getDrawData()->getShader()->setMatrix4f("uModelView", modelView, true);
    glDrawElements(GL_TRIANGLES, gameObject.getDrawData()->getMesh()->getPrimitive()->getIndicesCount(), GL_UNSIGNED_INT, 0);
    gameObject.getDrawData()->getMesh()->getVertexArray()->unbind();
}
void Renderer::drawUntextured(GameObject& gameObject, bool scaled) {
    glm::mat4 modelView = glm::mat4(1.0f);
    modelView = glm::translate(modelView, glm::vec3(glm::vec2(gameObject.getPositionX(), gameObject.getPositionY()), 0.0f));
    modelView = glm::rotate(modelView, glm::radians(gameObject.getRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
    if (!scaled) {
        modelView = glm::scale(modelView, glm::vec3(glm::vec2(gameObject.getSizeX(), gameObject.getSizeY()), 1.0f));
    }
    else {
        modelView = glm::scale(modelView, glm::vec3(glm::vec2(gameObject.getScaledSizeX(), gameObject.getScaledSizeY()), 1.0f));
    }
    gameObject.getDrawData()->getMesh()->getVertexArray()->bind();
    gameObject.getDrawData()->getShader()->setMatrix4f("uModelView", modelView, true);
    glDrawElements(GL_TRIANGLES, gameObject.getDrawData()->getMesh()->getPrimitive()->getIndicesCount(), GL_UNSIGNED_INT, 0);
    gameObject.getDrawData()->getMesh()->getVertexArray()->unbind();
}
void Renderer::colorBackground(glm::vec4 color) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);
}