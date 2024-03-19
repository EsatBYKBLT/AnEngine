#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Shader.h"
#include "Camera.h"

#include "Actor.h"

#include <string>
#include <iostream>

void size_callback(GLFWwindow* window, int width, int height);
void cursor_enter_callback(GLFWwindow* window, int entered);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);




class Renderer
{
public:

    Shader* shader;
    Camera camera;
    GLFWwindow* window;

    float SCR_WIDTH = 640, SCR_HEIGHT = 480;
    glm::mat4 model;

    GLFWwindow* init(std::string SCR_TITLE) {
		window = create_GLFWwindow(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE);
		init_glad();
        return window;
	}



    GLFWwindow* create_GLFWwindow(float width, float height, std::string title) {
        // |>----------<>----------<>----------<>----------<>----------<|
        // |>                    CREATE GLFW WINDOW                    <|
        // |>----------<>----------<>----------<>----------<>----------<|

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, false);

        // full screen 
        GLFWmonitor* MyMonitor = glfwGetPrimaryMonitor(); // The primary monitor.. Later Occulus?..

        const GLFWvidmode* mode = glfwGetVideoMode(MyMonitor);
        SCR_WIDTH = mode->width;
        SCR_HEIGHT = mode->height;
        std::cout << "Monitor width: " << SCR_WIDTH << "\theight: " << SCR_HEIGHT << std::endl;


        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title.c_str(), glfwGetPrimaryMonitor(), NULL);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            //return EXIT_FAILURE;
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);




        //glfwSetFramebufferSizeCallback(window, size_callback); // we bind callback to our size_callback func. 
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetCursorEnterCallback(window, cursor_enter_callback);
        glfwSetKeyCallback(window, key_callback);


        //https://www.glfw.org/docs/3.3/input_guide.html#cursor_standard
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


        return window;
    }

    void init_glad() {
        // |>----------<>----------<>----------<>----------<>----------<|
        // |>               LOAD OPENGL FUNCTION POINTERS              <|
        // |>----------<>----------<>----------<>----------<>----------<|

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(EXIT_FAILURE);
        }

    }

    void setClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }
    void setClearColor(float *rgba) {
        glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
    }
    void clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void enableBlending() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    //void drawActor(Actor& actor){
    //    drawActor(actor, vb, ib);
    //}

    //void drawActor(Actor& actor, VertexBuffer& vb, IndexBuffer& ib) {
    //    vb.SetBufferData(actor.getPoints().data(), sizeof(float) * actor.getPoints().size());
    //    ib.SetBufferData(actor.getIndicies().data(), sizeof(unsigned int) * actor.getIndicies().size());

    //    model = actor.transform.getTransform();
    //    glm::mat4 mvp = camera.GetCameraMatrix() * model;
    //    shader->setUniformMat4f("u_MVP", mvp);

    //    glDrawElements(GL_TRIANGLES, actor.getIndicies().size(), GL_UNSIGNED_INT, 0);
    //}


};
