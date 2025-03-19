#pragma once
#include "mounting.h"
#include "animator.h"
class AnimatorController :
    public mounting//������������
{
public:
    AnimatorController() {
        
    };
    void loadupdate(animator _animator) {
        std::vector<glm::mat4> transforms = _animator.GetFinalBoneMatrices();
        for (int i = 0; i < transforms.size(); ++i) {
            shaderlist[0]->use();
            shaderlist[0]->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
            shaderlist[0]->setBool("play", true);
        }
    }
    
    void play(animator animator) {
        animator.UpdateAnimation(optime.getdeltaTime());
    }

    void addanimator(GameObject* obj, animator* _animator) {//���ƶ��������µ�
        animators = new animator(*_animator);
        gameobjct = obj;
        animators->gameobjct = obj;
    }
    animator* animators;
};

int addAnimatorController(GameObject* obj, AnimatorController* actr) {
    //int tag = mountingadd(obj, actr);//�������
    obj->mountinglist.push_back(actr);
    obj->mountinglist.back()->gameobjct = obj;
    //if (tag == 1|| tag == 2) {
    //    return tag;
    //}
    std::cout << obj->name;
    obj->Drawmountinglist.emplace(obj->Drawmountinglist.begin(), actr->animators);//��ӿɻ���
    return 0;
}
void addanimator() {

}
