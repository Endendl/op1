#pragma once
#include "GameObject.h"

//#include "ImGui/imgui.h"
//#include "ImGui/imgui_impl_glfw.h"
//#include "ImGui/imgui_impl_opengl3.h"

class imgui_ui :
    public GameObject
{
    //imgui_ui();
    
    void Draw() override {
        //ui≥ı ºªØ
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

};

