#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer.h"
#include "Machine.h"




class UI
{

    float clear_color[4]{ .30,.30,.50, 1};

public:
    Renderer* renderer{};
    Machine* machine{};

	void init(GLFWwindow* window) {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 440");
        //ImGui variables: 
        //bool show_demo_window = true;
        //bool show_another_window = false;
	}


    void render() {

        // render imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        menuBar();
        test1();
        test2();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    void menuBar() {
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

    void test1() {
        ImGui::Begin("test");

        if (ImGui::ColorEdit4("bg color", clear_color))
            renderer->setClearColor(clear_color);


        ImGui::End();
    }

    void test2() {
        ImGui::Begin("test2");

        if (ImGui::ColorEdit4("bg color", clear_color))
            renderer->setClearColor(clear_color);

        ImGui::End();
    }
};




