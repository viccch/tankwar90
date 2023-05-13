//
// Created by Srf on 2017/10/5.
//

#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <stb_image.h>

std::map<std::string, std::shared_ptr<Texture2D>> ResourceManager::textures;
std::map<std::string, std::shared_ptr<Shader>> ResourceManager::shaders;
std::map<std::string, std::string> ResourceManager::bgms;

std::string ResourceManager::getBGM(std::string name) {
    return bgms[name];
}

std::string ResourceManager::loadBGM(const char* file_path,const char* name ) {
    bgms[name] = file_path;
    return bgms[name];
}

std::shared_ptr<Shader> ResourceManager::loadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name) {
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return shaders[name];
}

std::shared_ptr<Shader> ResourceManager::getShader(std::string name) {
    return shaders[name];
}


std::shared_ptr<Texture2D> ResourceManager::loadTexture(const GLchar* file, GLboolean alpha, std::string name) {
    textures[name] = loadTextureFromFile(file, alpha);
    textures[name]->name = name;
    // std::cout << textures[name].ID << std::endl;
    return textures[name];
}


std::shared_ptr<Texture2D> ResourceManager::getTexture(std::string name) {
    return textures[name];
}

void ResourceManager::clear() {

    for (auto& item : shaders) {
        std::cout << "USE COUNT\t" << item.second.use_count() << "\t" << item.first << "\t" << item.second->ID << std::endl;
    }
    for (auto& item : textures) {
        std::cout << "USE COUNT\t" << item.second.use_count() << "\t" << item.first << "\t" << item.second->ID << std::endl;
    }
    textures.clear();
    shaders.clear();
}

std::shared_ptr<Shader> ResourceManager::loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile) {
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr) {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception& e) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    const GLchar* gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    auto shader = std::make_shared<Shader>();
    shader->compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

std::shared_ptr<Texture2D> ResourceManager::loadTextureFromFile(const GLchar* file, GLboolean alpha) {
    // Texture2D texture = Texture2D();
    auto texture = std::make_shared<Texture2D>();
    if (alpha) {
        texture->internal_format = GL_RGBA;
        texture->image_format = GL_RGBA;
    }
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load(file, &width, &height, &nrChannels, 0);
    texture->generate((GLuint)width, (GLuint)height, image);
    stbi_image_free(image);
    return texture;
}