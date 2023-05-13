

#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <iostream>
//#include <glad/glad.h>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "Shader.h"
#include "Direction.h"


class SpriteRenderer {
public:
    explicit SpriteRenderer(std::shared_ptr<Shader> shader);
    virtual ~SpriteRenderer();
    // virtual  void drawSprite(std::shared_ptr<Texture2D> texture, glm::vec2 position, glm::vec2 size);
    virtual  void draw_common(std::shared_ptr<Texture2D> texture, glm::vec2 position, glm::vec2 size, const glm::vec4& tex_info=glm::vec4(1,1,0,0));

protected:
    std::shared_ptr<Shader> shader;
    GLuint VAO, VBO, EBO;
    void initRenderData();
};


#endif //SPRITERENDERER_H
