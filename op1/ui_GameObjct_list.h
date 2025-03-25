#pragma once
#include "imgui_ui.h"
class ui_GameObjct_list :
    public imgui_ui
{
public:
    ui_GameObjct_list() {
        name = "GameObjct list";
        hobj = &stobj;
    }
    void start() override{
        ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_NoFocusOnAppearing); // 禁止自动获取焦点
    }
    void printobjlist(std::vector<GameObject*> _objlist) {
        if (_objlist.size() != 0) {
            for (int i = 0; i < objlist.size(); i++) {
                if (ImGui::Button(objlist[i]->name.c_str())) {
                    setmasterobj(objlist[i]);
                }
                //ImGui::Text(objlist[i]->name.c_str());
            }
        }
    }

    void UIDraw() override {
        objlist.clear();
        ImVec2 window_size = ImGui::GetWindowSize();
        //ImGui::BeginMainMenuBar();
        GameObject* h = hobj->nextOBJCT;
        for (int i = 0; h != linknode; i++) {//加载队列
            //objnames[0] = h->name.c_str();
            objlist.push_back(h);
            h = h->nextOBJCT;
        }

        if (ImGui::CollapsingHeader(name.c_str(),  ImGuiTreeNodeFlags_Framed)) {//创建子窗口 //
            //ImGuiTreeNodeFlags_DefaultOpen - 默认展 ImGuiTreeNodeFlags_None - 默认折叠（不指定时的默认行为） ImGuiTreeNodeFlags_Framed - 带边框样式
            ImGui::BeginChild("Scrolling", ImVec2(window_size.x - 10, window_size.y - 75), true);//创建折叠分组
            printobjlist(objlist);
            ImGui::EndChild();
            if (Gui::masterobj != NULL) {
                ImGui::Text(Gui::masterobj->name.c_str());
            }
            else {
                ImGui::Text("NULL");
            }
            //if (ImGui::BeginCombo("111", objnames)) {
            //    
            //    ImGui::EndCombo();
            //}
        }    
       // }
        //ImGui
    }
    GameObject* hobj;
char* objnames;
};

