#include <iostream>

#include "pch.h"

#include "glm/gtx/string_cast.hpp"
#include "GameObject.h"
#include "GraphicDevice.h"
#include "CubeObject.h"
#include "PyramidObject.h"
#include "PrismObject.h"

#include "Camera.h"
#include <functional>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void update(GLFWwindow* window);
void render();
void checkForNewObj(GLFWwindow* window);
void init();

// Screen dimansion
unsigned int width = 1920, height = 1080;

// App globals
GraphicDevice device;
vector<GameObject*> objects;
Camera* camera;

int main(int argc, char** argv)
{

    // Initializing window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    init();

    while (!glfwWindowShouldClose(window))
    {
        update(window);
        render();
        if(!device.changeMode)
            checkForNewObj(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void init()
{
    camera = new Camera(width, height);
    camera->Setup();
    device.SetupDevice();
    device.SetCamera(camera);
    auto cube = new CubeObject(&device);
    cube->SetPosition(glm::vec3(5, 5, 5));
    objects.push_back(cube);
    cube = new CubeObject(&device);
    cube->SetPosition(glm::vec3(0, 0, -6));
    objects.push_back(cube);

    device.NoMoreChange();



    for (auto object = objects.begin(); object != objects.end(); object++)
    {
        (*object)->Render();
    }
}

void update(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        device.NoMoreChange();

    camera->Update(window);

        for (auto object = objects.begin(); object != objects.end(); object++)
        {
            if ((*object)->changeMode) {
                if (!device.changeMode) {
                    (*object)->NoMoreChange();
                }
                else (*object)->Update(window);
            }
        }
    
    
}

void render()
{

    unsigned int projLoc = glGetUniformLocation(device.GetShader()->ID, "projection");
    unsigned int viewLoc = glGetUniformLocation(device.GetShader()->ID, "view");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    device.Render(&objects);

}

void checkForNewObj(GLFWwindow* window) {
    //create new object
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        std::cout << "presssssssssssssss        ccccccccc" << std::endl;
        auto cube = new CubeObject(&device);
        glm::vec3 v1 = camera->GetPosition();
        glm::vec3 v2 = camera->GetForward();
        glm::vec3 pos = glm::vec3(v1.x + 3.0f * v2.x, v1.y + 3.0f * v2.y, v1.z - 3.0f * v2.z);
        std::cout << glm::to_string(v1) << std::endl;
        std::cout << glm::to_string(pos) << std::endl;
        cube->SetPosition(pos);
        objects.push_back(cube);
        device.SetChangeMode();
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        std::cout << "presssssssssssssss        ppppppppppppppppp" << std::endl;
        auto pyramid = new PyramidObject(&device);
        glm::vec3 v1 = camera->GetPosition();
        glm::vec3 v2 = camera->GetForward();
        glm::vec3 pos = glm::vec3(v1.x + 3.0f * v2.x, v1.y + 3.0f * v2.y, v1.z - 3.0f * v2.z);
        pyramid->SetPosition(pos);
        objects.push_back(pyramid);
        device.SetChangeMode();
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        std::cout << "presssssssssssssss        zzzzzzzzzzzzzzzz" << std::endl;
        auto prism = new PrismObject(&device);
        glm::vec3 v1 = camera->GetPosition();
        glm::vec3 v2 = camera->GetForward();
        glm::vec3 pos = glm::vec3(v1.x + 3.0f * v2.x, v1.y + 3.0f * v2.y, v1.z - 3.0f * v2.z);
        prism->SetPosition(pos);
        objects.push_back(prism);
        device.SetChangeMode();
    }

    for (auto object = objects.begin(); object != objects.end(); object++)
    {
        (*object)->Render();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);
    camera->SetViewPortSize(w, h, true);
    width = w;
    height = h;
}