#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "Renderer.h"
#include "Machine.h"
#include "Texture.h"

#include "Cylinder.h"
#include "Cube.h"
#include "Quad.h"
#include "Sphere.h"

class UI
{
    float clear_color_[4]{ .30,.30,.50, 1};

public:
    Renderer* renderer_{};
    Machine* machine_{};
    Scene* scene{};

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
        //Test1();
        Test2();
        //generateMesh();

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

        ImGui::Image((void*)(intptr_t)texture->getID(), ImVec2(600, 600), { 0, 1 }, { 1, 0 });//ImVec2(texture->getWidth(), texture->getHeight()), { 0, 1 }, { 1, 0 });
        ImGui::End();
    }

    void generateMesh() {
        ImGui::Begin("Generate Mesh");

        static std::string selected;
        std::vector<std::string> items = { "Cube", "Cylinder", "Quad", "Sphere"};
        static int item_current_idx = 0;                    // Here our selection data is an index.
        std::string combo_label = items[item_current_idx];  // Label to preview before opening the combo(technically could be anything)(
        if (ImGui::BeginCombo("Mesh Type", combo_label.c_str()))
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
                scene->add(Cube());   
            }
            else if (item_current_idx == 1) {
                scene->add(Cylinder());
            }
            else if (item_current_idx == 2) {
                scene->add(Quad());
            }
            else if (item_current_idx == 3) {
                scene->add(Sphere());
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }


        ImGui::Text(selected.c_str());





        ImGui::End();

    }

    //void rightClick() {
    //    if (ImGui::GetIO().MouseClicked[1])
    //    {
    //        ImGuiContext& g = *GImGui;
    //        if (g.OpenedPopupStack.size() > 0)
    //            g.OpenedPopupStack.pop_back();

    //        ImGui::OpenPopup("test");
    //    }
    //}
};




