#pragma once
#include "imgui_ui.h"
class ui_Global_variables :
    public imgui_ui
{
public:
    ui_Global_variables(){
        name = "Global variables";
    }
    float pickerColor[3];
    glm::vec3 FToGlmVec3(float a[]) {
        if (a[0] != NULL && a[1] != NULL, a[2] != NULL) {
            return glm::vec3(a[0], a[1], a[2]);
        }
        else
        {
            return glm::vec3(0.0f, 0.0f, 0.0f);
        }
    }
    
    void SETcolor(glm::vec3 &a) {
        pickerColor[0] = Global_variables::Globalcolor.x;
        pickerColor[1] = Global_variables::Globalcolor.y;
        pickerColor[2] = Global_variables::Globalcolor.z;
        if (ImGui::CollapsingHeader("Global color", ImGuiTreeNodeFlags_Framed)) {

            ImGui::ColorPicker3("Ê°É«Æ÷", pickerColor, ImGuiColorEditFlags_DisplayRGB);

            Global_variables::Globalcolor = FToGlmVec3(pickerColor);
        }
    }
    void UIDraw() override {
        const float input_width = 90.0f;
       
        SETcolor(Global_variables::Globalcolor);
        if (ImGui::CollapsingHeader("impart model", ImGuiTreeNodeFlags_Framed)) {
            static char text[512] = "n"; // »º³åÇøĞè×ã¹»´ó

            if (ImGui::InputText("path", text, IM_ARRAYSIZE(text))) {
            }
            if (ImGui::Button("lodeing")) {
                std::string load(text);
                DObjctadd(new model(load));
                linknode->backDOBJECT->thisshader = shaderlist[0];
            }
        }

    }
};

