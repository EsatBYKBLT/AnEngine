#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <iostream>
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include "UI.h"
#include "Renderer.h"
#include "Engine.h"

#include "Cylinder.h"
#include "Cube.h"
#include "Quad.h"
#include "Sphere.h"
#include "Texture.h"


void processInput(GLFWwindow* window);
Renderer renderer;
Engine engine;

static double lastX = 0, lastY = 0; // Mouse

int main() {
    renderer.Init("An Engine");

    std::vector<Actor> actors;
    Actor a1, a2, a3, a4, a5;
    a1 = Quad();
    a2 = Cube(); 
    a3 = Cylinder();
    a4 = Sphere();
    a1.transform.setLocation(000, 000, 0);
    a2.transform.setLocation(000, 300, 0);
    a3.transform.setLocation(300, 000, 0);
    a4.transform.setLocation(300, 300, 0);
    actors.push_back(a1);
    actors.push_back(a2);
    actors.push_back(a3);
    actors.push_back(a4);

    

    // |>----------<>----------<>----------<>----------<>----------<|
    // |>                         TEXTURE                          <|
    // |>----------<>----------<>----------<>----------<>----------<|
    Texture horse("res/horse-face.png"), face("res/tears-of-joy.png");
    
    Image image(100,100);
    image.fill(0xFF00FF00);
    Texture generated(image);

    Texture::setActiveTexture(GL_TEXTURE0); 
    face.bind();
    
    renderer.getShader()->SetUniform1i("texture1", 0);
    
    renderer.enableBlending();
    renderer.enableDepthTest();
    //renderer.va->Bind();


    //UI ui;
    UI ui;
    ui.Init(renderer.window);
    ui.texture = &face;

    // |>----------<>----------<>----------<>----------<>----------<|
    // |>                       RENDER LOOP                        <|
    // |>----------<>----------<>----------<>----------<>----------<|



    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    renderer.camera->SetProjection(1920, 1080, 10);

    while (!glfwWindowShouldClose(renderer.window)) {
        engine.t(glfwGetTime()); //update time 

        processInput(renderer.window);
        
        renderer.clear();

        for (auto& i : actors)
            i.transform.setRotation(glm::vec3(0, 0, 0));

        for (auto& i : actors) 
            renderer.drawActor(i);
        
        static int counter{};
        if (counter++ > 10) {
            if (ui.texture == &face) {
                ui.texture = &generated;
                generated.bind();
            }
            else {
                ui.texture = &face;
                face.bind();
            }

            counter = 0;
        }
        ui.Render();


        glfwSwapBuffers(renderer.window);
        glfwPollEvents();
    }

    renderer.terminate();
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

    float cameraSpeed = static_cast<float>(250 * engine.time());
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

    renderer.camera->Move(deltaLocation * cameraSpeed);
    //glm::mat4 mvp = renderer.camera->GetCameraMatrix() * model;
    //renderer.getShader()->setUniformMat4f("u_MVP", mvp);
}


void size_callback(GLFWwindow* window, int width, int height) {
    //std::cout << "New width: " << width << "\theight: " << height << std::endl;

    //camera.SetProjection(width, height,10);
    //glm::mat4 mvp = camera.GetCameraMatrix() * model;
    //shader.setUniformMat4f("u_MVP", mvp);

    //glViewport(0, 0, width, height);
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
    renderer.camera->Rotate(glm::vec3(deltaY, deltaX,  0));
    lastX = xpos;
    lastY = ypos;

    //static double lastX, lastY;
}





//// render imgui
//ImGui_ImplOpenGL3_NewFrame();
//ImGui_ImplGlfw_NewFrame();
//ImGui::NewFrame();

//ImGui::Begin("test");
////ImGui::ColorEdit4("bg color", clear_color);
////ImGui::DragFloat("Rotation", &rotation_angle);
//static float transform[3]{ 0,0,0 };
//static float size = 100;
//ImGui::InputFloat3("Transform", transform);
//ImGui::InputFloat("Size", &size);



//static std::string selected;
//std::vector<std::string> items = { "Cube", "Cylinder", "Quad", "Sphere"};
//static int item_current_idx = 0;                    // Here our selection data is an index.
//std::string combo_label = items[item_current_idx];  // Label to preview before opening the combo (technically could be anything)(
//if (ImGui::BeginCombo("combo 1", combo_label.c_str()))
//{
//    for (int n = 0; n < items.size(); n++)
//    {
//        const bool is_selected = (item_current_idx == n);
//        if (ImGui::Selectable(items[n].c_str(), is_selected)) {
//            item_current_idx = n;
//            std::cout << items[n] << std::endl;
//            selected = items[n];
//        }
//        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
//        if (is_selected)
//            ImGui::SetItemDefaultFocus();
//    }
//    ImGui::EndCombo();
//}



//if (ImGui::Button("Generate mesh")) {
//    if (item_current_idx == 0) {
//        auto i = Actor(Cube(size));
//        i.transform.setLocation(transform[0],transform[1], transform[2]);
//        actors.push_back(i);
//        

//    }

//    else if (item_current_idx == 1) {
//        auto i = Actor(Cylinder(size, size * 2, 16));
//        i.transform.setLocation(transform[0], transform[1], transform[2]);
//        actors.push_back(i);

//    }
//    else if (item_current_idx == 2) {
//        auto i = Actor(Quad());
//        i.transform.setLocation(transform[0], transform[1], transform[2]);
//        actors.push_back(i);

//    }
//    else if (item_current_idx == 3) {
//        auto i = Actor(Sphere());
//        i.transform.setLocation(transform[0], transform[1], transform[2]);
//        actors.push_back(i);

//    }
//    std::this_thread::sleep_for(std::chrono::milliseconds(300));
//}


//ImGui::Text(selected.c_str());

//if (ImGui::Button("face texture"))
//    face.bind();
//if (ImGui::Button("horse texture"))
//    horse.bind();


//ImGui::End();




//ImGui::Render();
//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());