#pragma once
#include "AnimatorController.h"
class testAnimatorCcontroller :
    public AnimatorController
{
public:
    testAnimatorCcontroller() {
        name = "testAnimatorCcontroller";

    };
    testAnimatorCcontroller(animator* _animator) {
        name = "testAnimatorCcontroller";
        animators = _animator;
    };

    void update() override {
        //std::cout << "testAnimatorCcontroller update\n";
        //if () {
            animators->setbool("f", Input->getkey("f"));

        //}
        animators->update();
    }

};
void addtestAnimatorController(model* obj, testAnimatorCcontroller* actr) {
    obj->mountinglist.push_back(actr);
    obj->mountinglist.back()->gameobjct = obj;
    //obj->mountinglist.push_back(actr->animators);
    //obj->mountinglist.back()->gameobjct = obj;
    //if (tag == 1|| tag == 2) {
    //    return tag;
    //}
    obj->Drawmountinglist.emplace(obj->Drawmountinglist.begin(), actr->animators);//ÃÌº”ø…ªÊ÷∆
    return;
}
