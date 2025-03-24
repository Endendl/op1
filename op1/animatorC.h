#pragma once
#include "animator.h"
class animatorC :
    public animator
{
public:
    animatorC() {
        name = "animatorC";
        m_CurrentTime = 0.0;
        m_FinalBoneMatrices.reserve(100);
        for (int i = 0; i < 100; i++)
            m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
    }
    void update() override {
        if (m_CurrentAnimation) {
           if (f) {
             if (m_CurrentAnimation != animationlist[0]) {
                 //std::cout << "animatorC update\n";
                PlayAnimation(this->animationlist[0]);
                std::cout << "ÇÐ»»\n";
             }
                UpdateAnimation(optime.getdeltaTime());
                playing = true;
                //std::cout << " ²¥·Å";
           }
           else {
               //std::cout << "animatorC update2\n";
                playing = false;
           }
        }
    }

    void Draw() override {
        //std::cout << "animatorC Draw\n";
        if (m_CurrentAnimation) {
            //std::cout << "animatorC rady\n";
            if (playing) {
                //std::cout << "animatorC play\n";
                loadupdate();
            }
            else {
                //std::cout << "animatorC play no\n";
                gameobjct->thisshader->setBool("play", false);
            }
        }
        //shaderlist[0]->setBool("play", false);
    }
    void setint(std::string _type, int mod) override{}
    void setbool(std::string _type, bool mod) override {
        if (_type == "f") f = mod;
        if (_type == "fr") fr = mod;
    }
    void setfloat(std::string _type, float mod) override {}

    bool f = false;
    bool fr = false;

};

