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

void Renderer::draw(GameObject& gameObject) {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    gameObject.getMesh()->getVertexArray()->bind();
    gameObject.getShader()->setMatrix4f("uTransform", transform, true);
    //gameObject.getShader()->use();
    glDrawElements(GL_TRIANGLES, gameObject.getMesh()->getPrimitive()->getIndicesCount(), GL_UNSIGNED_INT, 0);
    gameObject.getMesh()->getVertexArray()->unbind();
}

void Renderer::colorBackground(glm::vec4 color) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}