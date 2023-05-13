//
// Created by Srf on 2017/10/5.
//

#include "Texture2D.h"
#include <iostream>

Texture2D::Texture2D()
    :ID(0), width(0), height(0), internal_format(GL_RGB), image_format(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_NEAREST)
{
    glGenTextures(1, &this->ID);

    std::cout << "Texture2D() GenTextures\t" << ID << std::endl;

}

Texture2D::~Texture2D() {

    if (this->ID)
        glDeleteTextures(1, &ID);

    std::cout << "~Texture2D()\t" << ID << std::endl;

}


void Texture2D::generate(GLuint width, GLuint height, unsigned char* data) {

    this->width = width;
    this->height = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, width, height, 0, this->image_format, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const {

    glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
    glBindTexture(GL_TEXTURE_2D, this->ID);

}

