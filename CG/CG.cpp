#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <string>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Actor.h"

#include "Camera.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Cylinder.h"
#include "Cube.h"
#include "Quad.h"
#include "Sphere.h"


#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

void drawActor(Actor& actor, VertexBuffer& vb, IndexBuffer& ib);
void processInput(GLFWwindow* window);
void size_callback(GLFWwindow* window, int width, int height);
void cursor_enter_callback(GLFWwindow* window, int entered);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
GLFWwindow* create_GLFWwindow(float width, float height, std::string title);
void init_glad();


Camera camera; 
Shader shader; 


static double lastX = 0, lastY = 0; // Mouse

float SCR_WIDTH = 640, SCR_HEIGHT = 480;
std::string SCR_TITLE = "My 3D App";

glm::mat4 proj, view, model;
float currentFrame, lastFrame, deltaTime;


int main() {
    GLFWwindow* window = create_GLFWwindow(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE);
    init_glad();

    shader.Compile();
    shader.Bind();


    // |>----------<>----------<>----------<>----------<>----------<|
    // |>                      DEFINE VERTICES                     <|
    // |>----------<>----------<>----------<>----------<>----------<|

    std::vector<Actor> actors;

    // Position, Color, Texture Coordinates 
    unsigned int layout[]{ 3, GL_FLOAT,4,GL_FLOAT,2,GL_FLOAT };

    VertexArray va; va.Bind();
    VertexBuffer vb;// (actor1.getPoints().data(), sizeof(float) * actor1.getPoints().size());
    IndexBuffer ib;// (actor1.getIndicies().data(), sizeof(unsigned int) * actor1.getIndicies().size());

    vb.setLayout(layout,sizeof(layout));
    va.Unbind();
        

    // |>----------<>----------<>----------<>----------<>----------<|
    // |>                         TEXTURE                          <|
    // |>----------<>----------<>----------<>----------<>----------<|

    // load and create a texture 
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("res/horse-face.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    shader.SetUniform1i("texture1", 0);

    // enable blending 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // |>----------<>----------<>----------<>----------<>----------<|
    // |>                          CAMERA                          <|
    // |>----------<>----------<>----------<>----------<>----------<|
    camera = Camera(35, SCR_WIDTH, SCR_HEIGHT);



    // |>----------<>----------<>----------<>----------<>----------<|
    // |>                          ImGUI                           <|
    // |>----------<>----------<>----------<>----------<>----------<|

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 440");
    //ImGui variables: 
    //bool show_demo_window = true;
    //bool show_another_window = false;
    float clear_color[]{ 0.1f, 0.1f, 0.1f, 1.00f };




    // |>----------<>----------<>----------<>----------<>----------<|
    // |>                       RENDER LOOP                        <|
    // |>----------<>----------<>----------<>----------<>----------<|

    glEnable(GL_DEPTH_TEST);

    va.Bind();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float rotation_angle = 0;

    //glViewport(0, 0, 1920, 1080); 
    camera.SetProjection(1920, 1080, 10);

    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        
        // clear
        glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

        for (auto& i : actors)
            i.setRotation(glm::vec3(0, rotation_angle, 0));

        for(auto& i :actors)
            drawActor(i,vb,ib);


        // render imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("test");
        //ImGui::ColorEdit4("bg color", clear_color);
        //ImGui::DragFloat("Rotation", &rotation_angle);
        static float transform[3]{ 0,0,0 };
        static float size = 100;
        ImGui::InputFloat3("Transform", transform);
        ImGui::InputFloat("Size", &size);



        static std::string selected;
        std::vector<std::string> items = { "Cube", "Cylinder", "Quad", "Sphere"};
        static int item_current_idx = 0;                    // Here our selection data is an index.
        std::string combo_label = items[item_current_idx];  // Label to preview before opening the combo (technically could be anything)(
        if (ImGui::BeginCombo("combo 1", combo_label.c_str()))
        {
            for (int n = 0; n < items.size(); n++)
            {
                const bool is_selected = (item_current_idx == n);
                if (ImGui::Selectable(items[n].c_str(), is_selected)) {
                    item_current_idx = n;
                    std::cout << items[n] << std::endl;
                    selected = items[n];
                }
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }



        if (ImGui::Button("Generate mesh")) {
            if (item_current_idx == 0) {
                auto i = Actor(Cube(size));
                i.setLocation(transform[0],transform[1], transform[2]);
                actors.push_back(i);
                

            }

            else if (item_current_idx == 1) {
                auto i = Actor(Cylinder(size, size * 2, 16));
                i.setLocation(transform[0], transform[1], transform[2]);
                actors.push_back(i);

            }
            else if (item_current_idx == 2) {
                auto i = Actor(Quad());
                i.setLocation(transform[0], transform[1], transform[2]);
                actors.push_back(i);

            }
            else if (item_current_idx == 3) {
                auto i = Actor(Sphere());
                i.setLocation(transform[0], transform[1], transform[2]);
                actors.push_back(i);

            }
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }


        ImGui::Text(selected.c_str());


        ImGui::End();




        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}


void drawActor(Actor& actor, VertexBuffer& vb, IndexBuffer& ib) {
    vb.SetBufferData(actor.getPoints().data(), sizeof(float) * actor.getPoints().size());
    ib.SetBufferData(actor.getIndicies().data(), sizeof(unsigned int) * actor.getIndicies().size());

    model = actor.modelMatrix();
    glm::mat4 mvp = camera.GetCameraMatrix() * model;
    shader.setUniformMat4f("u_MVP", mvp);

    glDrawElements(GL_TRIANGLES, actor.getIndicies().size(), GL_UNSIGNED_INT, 0);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    //if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
        if (GLFW_CURSOR_DISABLED == glfwGetInputMode(window, GLFW_CURSOR))
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else {
            glfwGetCursorPos(window, &lastX, &lastY);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }


    //if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    //else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void processInput(GLFWwindow* window){

    float cameraSpeed = static_cast<float>(250 * deltaTime);
    glm::vec3 deltaLocation = glm::vec3(0.0f);


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        deltaLocation += glm::vec3(0, 0, -1); // to forward
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        deltaLocation += glm::vec3(0, 0, 1); // to backward

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        deltaLocation += glm::vec3(1, 0, 0); // to right
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        deltaLocation += glm::vec3(-1, 0, 0); // to left 

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        deltaLocation += glm::vec3(0, 1, 0); // to up 
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        deltaLocation += glm::vec3(0, -1, 0); // to down 

    camera.Move(deltaLocation * cameraSpeed);
    glm::mat4 mvp = camera.GetCameraMatrix() * model;
    shader.setUniformMat4f("u_MVP", mvp);
}


void size_callback(GLFWwindow* window, int width, int height) {
    //std::cout << "New width: " << width << "\theight: " << height << std::endl;

    //camera.SetProjection(width, height,10);
    //glm::mat4 mvp = camera.GetCameraMatrix() * model;
    //shader.setUniformMat4f("u_MVP", mvp);

    //glViewport(0, 0, width, height);
}

GLFWwindow* create_GLFWwindow(float width, float height, std::string title){
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





// |>----------<>----------<>----------<>----------<>----------<|
// |>                          MOUSE                           <|
// |>----------<>----------<>----------<>----------<>----------<|
void cursor_enter_callback(GLFWwindow* window, int entered){
    if (entered){
        glfwGetCursorPos(window, &lastX, &lastY);
        
    }
    else{
        // The cursor left the content area of the window
    }
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

    if (GLFW_CURSOR_NORMAL == glfwGetInputMode(window, GLFW_CURSOR))
        return;

    //std::cout << lastX-xpos << "-" << lastY-ypos << std::endl;
    double mouseSensitivity = 0.2;
    double deltaX = (lastX - xpos) * mouseSensitivity;
    double deltaY = (lastY - ypos) * mouseSensitivity;
    camera.Rotate(glm::vec3(deltaY, deltaX,  0));
    lastX = xpos;
    lastY = ypos;

    //static double lastX, lastY;
}


void init_glad(){
    // |>----------<>----------<>----------<>----------<>----------<|
    // |>               LOAD OPENGL FUNCTION POINTERS              <|
    // |>----------<>----------<>----------<>----------<>----------<|

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

}


