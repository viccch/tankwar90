//
// Created by Srf on 2017/10/5.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <memory>
#include <map>
#include <string>
//#include <glad/glad.h>
#include <GL/glew.h>

#include "Texture2D.h"
#include "Shader.h"

class ResourceManager {
public:
    static  std::map<std::string, std::string> bgms;
    static  std::string loadBGM(const char* file_path, const char* name);
    static  std::string getBGM(std::string);
    static  std::map<std::string, std::shared_ptr<Shader>> shaders;
    static  std::map<std::string, std::shared_ptr<Texture2D>> textures;
    static  std::shared_ptr<Shader> loadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);
    static  std::shared_ptr<Shader> getShader(std::string name);
    static  std::shared_ptr<Texture2D> loadTexture(const GLchar* file, GLboolean alpha, std::string name);
    static  std::shared_ptr<Texture2D> getTexture(std::string name);
    static  void clear();
private:
    static  std::shared_ptr<Shader>  loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);
    static  std::shared_ptr<Texture2D>  loadTextureFromFile(const GLchar* file, GLboolean alpha);
};


#endif //RESOURCEMANAGER_H
