//#include <bits/stdc++.h>

//#include <glad/glad.h>
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/Game.h"

#include <iostream>
#include <thread>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
float get_fps();
double lastTime = 0.0;
int nbFrames = 0;
GLFWwindow* window;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Game* game_ptr;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // 设为0不限制帧率，设为1则帧率60，2：30,1垂直同步
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    // // glad: load all OpenGL function pointers
    // // ---------------------------------------
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }

    glewInit();

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    // glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    /*Scope GAME*/
    {

        Game game(SCR_WIDTH, SCR_HEIGHT);
        game_ptr = &game;

        //
        game.init();

        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            get_fps();

            game.update();
            // render
            // ------
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            game.render();

            if (game.state == GameState::GAME_EXIT) {
                glfwSetWindowShouldClose(window, true);
            }

            glfwPollEvents();
            glfwSwapBuffers(window);
        }

    }

    glfwTerminate();
    ResourceManager::clear();

    return 0;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);


    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game_ptr->keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            game_ptr->keys[key] = GL_FALSE;
    }
}


float get_fps() {
    double currentTime = glfwGetTime();
    double delta = currentTime - lastTime;
    nbFrames++;
    if (delta >= 1.0) {
        std::cout << 1000.0 / double(nbFrames) << std::endl;

        double fps = double(nbFrames) / delta;

        std::stringstream ss;
        ss << " [" << fps << " FPS]";

        glfwSetWindowTitle(window, ss.str().c_str());

        nbFrames = 0;
        lastTime = currentTime;
    }
    return nbFrames;
}