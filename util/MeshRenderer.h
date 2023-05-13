#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <iostream>
#include <vector>
//#include <glad/glad.h>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

class MeshRenderer {

public:
    explicit MeshRenderer(std::shared_ptr<Shader>shader);
    ~MeshRenderer();
    void draw();
    void initRenderData(const std::vector<std::pair< glm::vec2, glm::vec2>>& mesh);

private:
    std::shared_ptr<Shader>shader;
    GLuint VAO, VBO;

    std::vector<float> vertices;
};

#endif /*MESHRENDERER_H*/