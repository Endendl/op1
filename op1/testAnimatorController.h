#pragma once
#include "AnimatorController.h"
class testAnimatorCcontroller :
    public AnimatorController
{
public:
    testAnimatorCcontroller() {
        name = "testAnimatorCcontroller";
    };

    void update() override {
        //animators->setbool("f", true);
        //animators->update();
    }

};
void addtestAnimatorController(model* obj, testAnimatorCcontroller* actr) {
    obj->mountinglist.push_back(actr);
    obj->mountinglist.back()->gameobjct = obj;
    //if (tag == 1|| tag == 2) {
    //    return tag;
    //}
    obj->Drawmountinglist.emplace(obj->Drawmountinglist.begin(), actr->animators);//Ìí¼Ó¿É»æÖÆ
    return;
}
