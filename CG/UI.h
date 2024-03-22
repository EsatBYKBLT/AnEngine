#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer.h"
#include "Machine.h"
#include "Texture.h"

class UI
{
    float clear_color_[4]{ .30,.30,.50, 1};

public:
    Renderer* renderer_{};
    Machine* machine_{};

    Texture* texture;

	void Init(GLFWwindow* window) {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 440");
        //ImGui variables: 
        //bool show_demo_window = true;
        //bool show_another_window = false;
	}


    void Render() {

        // render imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        MenuBar();
        Test1();
        Test2();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    void MenuBar() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Create")) {
                }
                if (ImGui::MenuItem("Open", "Ctrl+O")) {
                }
                if (ImGui::MenuItem("Save", "Ctrl+S")) {
                }
                if (ImGui::MenuItem("Save as..")) {
                }
                if (ImGui::MenuItem("Exit")) {
                    //glfwSetWindowShouldClose(window,true);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void Test1() {
        ImGui::Begin("test");

        if (ImGui::ColorEdit4("bg color", clear_color_))
            renderer_->setClearColor(clear_color_);


        ImGui::End();
    }

    void Test2() {
        ImGui::Begin("OpenGL Texture Text");
        ImGui::Text("pointer = %x", texture->getID());
        ImGui::Text("size = %d x %d", 100, 100);

        ImGui::Image((void*)(intptr_t)texture->getID(), ImVec2(200,200), { 0, 1 }, { 1, 0 });//ImVec2(texture->getWidth(), texture->getHeight()), { 0, 1 }, { 1, 0 });
        ImGui::End();
    }

};




