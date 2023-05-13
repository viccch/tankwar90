#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(std::shared_ptr<Shader>shader) {
    this->shader = shader;
    this->VAO = 0;
}

MeshRenderer::~MeshRenderer() {
    if (this->VAO)
        glDeleteVertexArrays(1, &this->VAO);
    std::cout << "~MeshRenderer()" << std::endl;
}

void MeshRenderer::draw() {

    this->shader->use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, vertices.size());

    glBindVertexArray(0);
}


void MeshRenderer::initRenderData(const std::vector<std::pair< glm::vec2, glm::vec2>>& mesh) {

    // std::vector<float> vertices;

    for (auto& pr : mesh) {
        vertices.push_back(pr.first.x);
        vertices.push_back(pr.first.y);
        vertices.push_back(0);
        vertices.push_back(pr.second.x);
        vertices.push_back(pr.second.y);
        vertices.push_back(0);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}