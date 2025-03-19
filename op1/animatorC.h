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
        if (f) {
            if (m_CurrentAnimation != animationlist[0]) {
                PlayAnimation(this->animationlist[0]);
                UpdateAnimation(optime.getdeltaTime());
            }
            playing = true;
        }
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

