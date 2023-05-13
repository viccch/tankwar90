

#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(std::shared_ptr<Shader>  shader) {
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    std::cout << "~SpriteRenderer()" << std::endl;
}


void SpriteRenderer::draw_common(std::shared_ptr<Texture2D> texture, glm::vec2 position, glm::vec2 size, const glm::vec4& tex_info) {
    // int x_c,int y_c,int x_i,int y_i;
    this->shader->use();
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, glm::vec3(position, 0.0f));
    //model = glm::scale(model, glm::vec3(size, 1.0f));
    model = glm::translate(model, glm::vec3(position + 0.5f * size, 0.0f));
    model = glm::scale(model, glm::vec3(size*0.5f, 1.0f));
    shader->setMatrix4("model", model);

    this->shader->setVector4f("info", tex_info);
    texture->bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// void SpriteRenderer::drawSprite(std::shared_ptr<Texture2D>  texture, glm::vec2 position, glm::vec2 size) {
//     this->shader->use();

//     glm::mat4 model = glm::mat4(1.0f);
//     model = glm::translate(model, glm::vec3(position, 0.0f));
//     model = glm::scale(model, glm::vec3(size, 1.0f));
//     shader->setMatrix4("model", model);

//     texture->bind();

//     glBindVertexArray(VAO);
//     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//     glBindVertexArray(0);
// }

void SpriteRenderer::initRenderData() {

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // float vertices[] = {
    //     // positions          // texture coords
    //     1.0f,  1.0f, 0.0f,   1.0f, 1.0f, // top right
    //     1.0f,  0.0f, 0.0f,   1.0f, 0.5f, // bottom right
    //     0.0f,  0.0f, 0.0f,   0.5f, 0.5f, // bottom left
    //     0.0f,  1.0f, 0.0f,   0.5f, 1.0f  // top left 
    // };

    //float vertices[] = {
    //    // positions          // texture coords
    //    1.0f,  1.0f, 0.0f,   1.0f, 1.0f, // top right
    //    1.0f,  0.0f, 0.0f,   1.0f, 0.0f, // bottom right
    //    0.0f,  0.0f, 0.0f,   0.0f, 0.0f, // bottom left
    //    0.0f,  1.0f, 0.0f,   0.0f, 1.0f  // top left 
    //};

    float vertices[] = {
        // positions          // texture coords
        1.0f,  1.0f, 0.0f,   1.0f, 1.0f, // top right
        1.0f,  -1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -1.0f,  -1.0f, 0.0f,   0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}