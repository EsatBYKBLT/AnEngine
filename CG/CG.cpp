#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <iostream>
#include <vector>

#include "UI.h"
#include "Renderer.h"
#include "Engine.h"
#include "Scene.h"

#include "Texture.h"

#include "Vec3.h"
#include "Ray.h"

#include <cstdint>

void processInput(GLFWwindow* window);
Renderer renderer;
Engine engine;

static double lastX = 0, lastY = 0; // Mouse


bool hitSphere(const Vec3& center, double radius, const Ray& r) {
    Vec3 oc = r.origin - center;
    auto rdir = r.direction;

    auto a = rdir.dot(rdir);
    auto b = 2.0 * oc.dot(r.direction);
    auto c = oc.dot(oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    return (discriminant >= 0);
}

int main() {
    renderer.Init("An Engine");

    Scene scene;
    Actor actors[]{ Quad(),Cube(),Cylinder(),Sphere() };
    for (int i = 0; i < 4; i++) {
        actors[i].transform.setLocation(i*300, 000, 0);
        scene.add(actors[i]);
    }


    // |>----------<>----------<>----------<>----------<>----------<|
    // |>                         TEXTURE                          <|
    // |>----------<>----------<>----------<>----------<>----------<|
    Texture horse("res/horse-face.png"), face("res/tears-of-joy.png");
    
    Image image(600,600);
    image.fill(0xff55aa55);

    //image.fill(0xFF00FF00);
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
    ui.scene = &scene;
    ui.texture = &face;

    // |>----------<>----------<>----------<>----------<>----------<|
    // |>                       RENDER LOOP                        <|
    // |>----------<>----------<>----------<>----------<>----------<|
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    renderer.camera->SetProjection(1920, 1080, 10);

    ui.texture = &generated;

    while (!glfwWindowShouldClose(renderer.window)) {
        engine.t(glfwGetTime()); //update time 

        processInput(renderer.window);

        renderer.clear();

        renderer.drawScene(scene);



        static float ii = 0; ii += 0.01;
        uint8_t r = (sin(ii) + 1) * 128;
        image.fill(0xff55aa00 | r);
        generated.loadImage(image);
        //ui.texture = &generated;

        face.bind();


        //static int counter{};
        //if (counter++ > 100) {
        //    if (ui.texture == &face) {
        //        ui.texture = &generated;
        //        //generated.bind();
        //    }
        //    else {
        //        ui.texture = &face;
        //        //face.bind();
        //    }

        //    counter = 0;
        //}

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





//ImGui::Begin("test");
////ImGui::ColorEdit4("bg color", clear_color);
////ImGui::DragFloat("Rotation", &rotation_angle);
//static float transform[3]{ 0,0,0 };
//static float size = 100;
//ImGui::InputFloat3("Transform", transform);
//ImGui::InputFloat("Size", &size);



//ImGui::End();




//ImGui::Render();
//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());