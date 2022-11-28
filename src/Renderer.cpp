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
    gameObject.getMesh()->getVertexArray()->bind();
    gameObject.getShader()->use();
    glDrawElements(GL_TRIANGLES, gameObject.getMesh()->getVertexCount(), GL_UNSIGNED_INT, 0);
    gameObject.getMesh()->getVertexArray()->unbind();
}

void Renderer::colorBackground(glm::vec4 color) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}