#pragma once
#include "imgui_ui.h"
class ui_objmounts_list :
    public imgui_ui
{
public:
    ui_objmounts_list() {
        name = "mount list";
        tag = "UI";
    };
    GameObject* p;
    bool reset;
    int index = 0;
    void start() override {
        ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_NoFocusOnAppearing); // 禁止自动获取焦点
    }
    void UIDraw() override{
        reset = false;
        if (p != Gui::masterobj) {
            p = Gui::masterobj;
            reset = true;
        }
        if (p != NULL) {
            ImGui::Text(p->tag.c_str());
            mouseR();
        }
        else {
            ImGui::Text("NULL");
        }

      
        printansform(p);
        printmount(p);


    }
    void mouseR() {//右键菜单
        if (ImGui::BeginPopupContextWindow("window_context_menu"))
        {
            ImGui::Text("addmount");
            if (ImGui::MenuItem("ad?")) {
            
            }
            if (ImGui::BeginMenu("collision")) {
                if (ImGui::MenuItem("CubeCollision")) {
                    add_CubeCollision(p, 0, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f);
                }
                if (ImGui::MenuItem("SphereCollision")) {
                    add_SphereCollision(p, 0, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f);
                }
                if (ImGui::MenuItem("CapsuleCollision")) {
                    add_CapsuleCollision(p, 0, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, -1.0f, 1.0f);
                }
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }
    }

    void printansform(GameObject* _obj) {
        if (_obj != NULL) {
            const float input_width = 90.0f;
            if (ImGui::CollapsingHeader("transform", ImGuiTreeNodeFlags_Framed)) {
                // X 输入框
                ImGui::Text("Position:");          // 标签
                ImGui::Text("X:");          // 标签
                ImGui::SameLine();          // 保持在同一行
                ImGui::SetNextItemWidth(input_width); //宽度
                ImGui::InputFloat("##PX", &_obj->transform.Position.x,  IM_ARRAYSIZE(&_obj->transform.Position.x)); // "##X" 隐藏标签，避免重复显示
                // Y 输入框
                ImGui::SameLine();
                ImGui::Text("Y:");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(input_width);
                ImGui::InputFloat("##PY", &_obj->transform.Position.y,  IM_ARRAYSIZE(&_obj->transform.Position.y));
                // Z 输入框
                ImGui::SameLine();
                ImGui::Text("Z:");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(input_width);
                ImGui::InputFloat("##PZ", &_obj->transform.Position.z,  IM_ARRAYSIZE(&_obj->transform.Position.z));


                ImGui::Text("Rotate:");          // 标签
                ImGui::Text("X:");          // 标签
                ImGui::SameLine();          // 保持在同一行
                ImGui::SetNextItemWidth(input_width); //宽度
                ImGui::InputFloat("##RX", &_obj->transform.rotate.x,  IM_ARRAYSIZE(&_obj->transform.rotate.x)); // "##X" 隐藏标签，避免重复显示
                // Y 输入框
                ImGui::SameLine();
                ImGui::Text("Y:");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(input_width);
                ImGui::InputFloat("##RY", &_obj->transform.rotate.y,  IM_ARRAYSIZE(&_obj->transform.rotate.y));
                // Z 输入框
                ImGui::SameLine();
                ImGui::Text("Z:");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(input_width);
                ImGui::InputFloat("##RZ", &_obj->transform.rotate.z,  IM_ARRAYSIZE(&_obj->transform.rotate.z));
                
                
                ImGui::Text("Scale:");          // 标签
                ImGui::Text("X:");          // 标签
                ImGui::SameLine();          // 保持在同一行
                ImGui::SetNextItemWidth(input_width); //宽度
                ImGui::InputFloat("##SX", &_obj->transform.Scale.x,  IM_ARRAYSIZE(&_obj->transform.Scale.x)); // "##X" 隐藏标签，避免重复显示
                // Y 输入框
                ImGui::SameLine();
                ImGui::Text("Y:");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(input_width);
                ImGui::InputFloat("##SY", &_obj->transform.Scale.y,  IM_ARRAYSIZE(&_obj->transform.Scale.y));
                // Z 输入框
                ImGui::SameLine();
                ImGui::Text("Z:");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(input_width);
                ImGui::InputFloat("##SZ", &_obj->transform.Scale.z,  IM_ARRAYSIZE(&_obj->transform.Scale.z));
            }
        }
    }

    void printmount(GameObject* _obj) {
        if (_obj != NULL) {
            for (int i = 0; i < p->mountinglist.size(); i++) {
                std::string tmp = p->mountinglist[i]->name + "###" + std::to_string(index++);
                if (ImGui::CollapsingHeader(tmp.c_str(), ImGuiTreeNodeFlags_Framed)) {
                    std::string tags = "tag: " + p->mountinglist[i]->tag;
                    ImGui::Text(tags.c_str());
                }
            }
        }
       
    }

};

