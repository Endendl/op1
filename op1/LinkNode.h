#pragma once
#ifndef LINKNODE_H
#define LINKNODE_H
#include "init_tool.h"
class LinkNode :
    public GameObject
{
public:

    LinkNode() {};
    GameObject* backDOBJECT;
    GameObject* backCOBJECT;
    void update() override {
        //Input->updatend();//Í£Ö¹¸üÐÂ

    }
	void Draw() override {
        //for (shaderlist i = 0; i < length; i++)
        //{
        //
        //}
        //shaderlist[0]->setBool("play", true);
	}
};

LinkNode* linknode = new LinkNode();
void DObjctadd(GameObject* obj) {
    linknode->backDOBJECT->nextOBJCT = obj;
    obj->nextOBJCT = linknode;
    linknode->backDOBJECT = obj;
    objctNumber++;
}
void CObjctDadd(GameObject* obj) {
    linknode->backCOBJECT->nextOBJCT = obj;
    obj->nextOBJCT = linknode;
    linknode->backCOBJECT = obj;
    objctNumber++;
}
#endif // LINKNODE_H
