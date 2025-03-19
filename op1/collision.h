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
    void update() override {//每帧获取碰撞队列
        
    }
    glm::vec3 center;
    glm::vec3 Pos;
    int Species;////0 球体 1方形 2胶囊

    virtual bool tosphere(SphereCollision& _collisions) = 0;
    virtual bool tocube(CubeCollision& _collisions) = 0;
    virtual bool tocapsule(CapsuleCollision& _collisions) = 0;
    std::vector<collision*> collisions;
    //static std::vector<collision*> collisionlist; // 存储所有碰撞体的指针
};
// 初始化静态成员变量
std::vector<collision*> collisionlist;



