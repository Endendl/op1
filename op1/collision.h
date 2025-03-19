#pragma once
#include "mounting.h"
#include "iostream"
class SphereCollision;
class CapsuleCollision;
class CubeCollision;
class collision :
    public mounting
{
public:
    collision() {
    };
    void update() override {//ÿ֡��ȡ��ײ����
        
    }
    glm::vec3 center;
    glm::vec3 Pos;
    int Species;////0 ���� 1���� 2����

    virtual bool tosphere(SphereCollision& _collisions) = 0;
    virtual bool tocube(CubeCollision& _collisions) = 0;
    virtual bool tocapsule(CapsuleCollision& _collisions) = 0;
    std::vector<collision*> collisions;
    //static std::vector<collision*> collisionlist; // �洢������ײ���ָ��
};
// ��ʼ����̬��Ա����
std::vector<collision*> collisionlist;



