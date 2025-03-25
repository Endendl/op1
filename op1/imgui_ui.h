#pragma once
#include "GameObject.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
namespace Gui {
    GameObject* masterobj;
}
class imgui_ui :
    public GameObject
{
public:
    imgui_ui() {
        name = "ui";
    };
    std::vector<GameObject*> objlist;
    
    void Draw() override {
        start();
        UIDraw();
        end();
    }
    virtual void start() {
        //ImGui::Begin(name.c_str());
        ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_NoFocusOnAppearing); // 禁止自动获取焦点
    }

    virtual void end() {
        ImGui::End();
    }

    int setmasterobj(GameObject* _obj) {
        if (_obj == NULL) {
            return 1;
        }
        Gui::masterobj = _obj;
        return 0;
    };
    virtual void UIDraw() {
        ImGui::ShowDemoWindow();
    };
};




