//
// Created by Srf on 2017/10/5.
//

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

//#include <glad/glad.h>
#include <GL/glew.h>
#include <string>

class Texture2D {
public:
    std::string name;
    GLuint ID;
    GLuint width, height; // Width and height of loaded image in pixels
    GLuint internal_format; // Format of texture object
    GLuint image_format; // Format of loaded image
    GLuint wrapS; // Wrapping mode on S axis
    GLuint wrapT; // Wrapping mode on T axis
    GLuint filterMin; // Filtering mode if texture pixels < screen pixels
    GLuint filterMax; // Filtering mode if texture pixels > screen pixels
    // Constructor (sets default texture modes)
    Texture2D();
    ~Texture2D();
    // Generates texture from image data
    void generate(GLuint width, GLuint height, unsigned char* data);
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void bind() const;
};


#endif //TEXTURE2D_H
