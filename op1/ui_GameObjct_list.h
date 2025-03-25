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
        ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_NoFocusOnAppearing); // ��ֹ�Զ���ȡ����
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
        for (int i = 0; h != linknode; i++) {//���ض���
            //objnames[0] = h->name.c_str();
            objlist.push_back(h);
            h = h->nextOBJCT;
        }

        if (ImGui::CollapsingHeader(name.c_str(),  ImGuiTreeNodeFlags_Framed)) {//�����Ӵ��� //
            //ImGuiTreeNodeFlags_DefaultOpen - Ĭ��չ ImGuiTreeNodeFlags_None - Ĭ���۵�����ָ��ʱ��Ĭ����Ϊ�� ImGuiTreeNodeFlags_Framed - ���߿���ʽ
            ImGui::BeginChild("Scrolling", ImVec2(window_size.x - 10, window_size.y - 75), true);//�����۵�����
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

