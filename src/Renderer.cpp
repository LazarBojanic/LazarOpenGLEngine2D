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

void Renderer::draw(GameObject& gameObject, glm::vec2 position, glm::vec2 size, float rotationRadians) {
    glm::mat4 modelView = glm::mat4(1.0f);
    modelView = glm::translate(modelView, glm::vec3(position, 0.0f));
    modelView = glm::rotate(modelView, glm::radians(rotationRadians), glm::vec3(0.0f, 0.0f, 1.0f));
    modelView = glm::scale(modelView, glm::vec3(size, 1.0f));
    
    gameObject.getMesh()->getVertexArray()->bind();
    gameObject.getTexture2D()->bind(0);
    gameObject.getShader()->setMatrix4f("uModelView", modelView, true);
    glDrawElements(GL_TRIANGLES, gameObject.getMesh()->getPrimitive()->getIndicesCount(), GL_UNSIGNED_INT, 0);
    gameObject.getMesh()->getVertexArray()->unbind();
}
void Renderer::drawUntextured(GameObject& gameObject, glm::vec2 position, glm::vec2 size, float rotationRadians) {
    glm::mat4 modelView = glm::mat4(1.0f);
    modelView = glm::translate(modelView, glm::vec3(position, 0.0f));
    modelView = glm::rotate(modelView, glm::radians(rotationRadians), glm::vec3(0.0f, 0.0f, 1.0f));
    modelView = glm::scale(modelView, glm::vec3(size, 1.0f));

    gameObject.getMesh()->getVertexArray()->bind();
    gameObject.getShader()->setMatrix4f("uModelView", modelView, true);
    glDrawElements(GL_TRIANGLES, gameObject.getMesh()->getPrimitive()->getIndicesCount(), GL_UNSIGNED_INT, 0);
    gameObject.getMesh()->getVertexArray()->unbind();
}

void Renderer::colorBackground(glm::vec4 color) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);
}