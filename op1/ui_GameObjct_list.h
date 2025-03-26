#pragma once
#include "imgui_ui.h"
class ui_GameObjct_list :
    public imgui_ui
{
public:
    ui_GameObjct_list() {
        name = "GameObjct list";
        tag = "UI";
        hobj = &stobj;
    }
    void start() override{
        ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_NoFocusOnAppearing); // ��ֹ�Զ���ȡ����
    }
    void printobjlist(std::vector<GameObject*> _objlist) {
        if (_objlist.size() != 0) {
            for (int i = 0; i < objlist.size(); i++) {
                std::string tmp = objlist[i]->name + "###" + std::to_string(i);
                if (ImGui::Button(tmp.c_str())) {
                    setmasterobj(objlist[i]);
                }
                //ImGui::Text(objlist[i]->name.c_str());
            }
        }
    }

    void printlight() {//�����Դ����
        if (1) {
            for (int i = 0; i < Lightlist.LightVector.size(); i++) {
                std::string tmp = Lightlist.LightVector[i].name + "###" + std::to_string(i);
                if (ImGui::Button(tmp.c_str())) {
                    setmasterobj(&Lightlist.LightVector[i]);
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

        if (ImGui::CollapsingHeader(name.c_str(),  ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_Framed)) { //�����۵�����
            //ImGuiTreeNodeFlags_DefaultOpen - Ĭ��չ ImGuiTreeNodeFlags_None - Ĭ���۵�����ָ��ʱ��Ĭ����Ϊ�� ImGuiTreeNodeFlags_Framed - ���߿���ʽ
            ImGui::BeginChild("gameobj", ImVec2(window_size.x - 10, window_size.y - 75), true);////�����Ӵ���
            printobjlist(objlist);
            ImGui::EndChild();
            
            
            //if (ImGui::BeginCombo("111", objnames)) {
            //    
            //    ImGui::EndCombo();
            //}
        }    
        if (ImGui::CollapsingHeader("LIGHT LIST", ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_Framed)) {//���б�

            ImGui::BeginChild("light", ImVec2(window_size.x - 10, window_size.y - 75), true);//�����Ӵ���
            printlight();
            ImGui::EndChild();
        }
        if (Gui::masterobj != NULL) {//���ѡ������
            ImGui::Text(Gui::masterobj->name.c_str());
        }
        else {
            ImGui::Text("NULL");
        }
       // }
        //ImGui
    }
    GameObject* hobj;
char* objnames;
};

