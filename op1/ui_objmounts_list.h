#pragma once
#include "imgui_ui.h"
class ui_objmounts_list :
    public imgui_ui
{
public:
    ui_objmounts_list() {
        name = "mount list";
    };
    GameObject* p;
    bool reset;

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
            ImGui::Text(p->name.c_str());
        }
        else {
            ImGui::Text("NULL");
        }
        printansform(p);
        printmount(p);
    }
    void printansform(GameObject* _obj) {
        if (_obj != NULL) {
            const float input_width = 90.0f;
            if (ImGui::CollapsingHeader("transform", ImGuiTreeNodeFlags_Framed)) {
                // X 输入框
                ImGui::Text("X:");          // 标签
                ImGui::SameLine();          // 保持在同一行
                ImGui::SetNextItemWidth(input_width); //宽度
                ImGui::InputFloat("##X", &_obj->transform.Position.x,  IM_ARRAYSIZE(&_obj->transform.Position.x)); // "##X" 隐藏标签，避免重复显示
                // Y 输入框
                ImGui::SameLine();
                ImGui::Text("Y:");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(input_width);
                ImGui::InputFloat("##Y", &_obj->transform.Position.y,  IM_ARRAYSIZE(&_obj->transform.Position.y));
                // Z 输入框
                ImGui::SameLine();
                ImGui::Text("Z:");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(input_width);
                ImGui::InputFloat("##Z", &_obj->transform.Position.z,  IM_ARRAYSIZE(&_obj->transform.Position.z));
            }
        }
    }

    void printmount(GameObject* _obj) {
        for (int i = 0; i <= p->mountinglist.size(); i++) {
            if (ImGui::CollapsingHeader(p->mountinglist[i]->name.c_str(), ImGuiTreeNodeFlags_Framed)) {
                std::string tags = "tag: " + p->mountinglist[i]->name;
                ImGui::Text(tags.c_str());
            }
        }
    }

};

