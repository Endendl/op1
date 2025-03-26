#pragma once
#include "collision.h"

class SphereCollision :
    public collision
{
public:
    SphereCollision(GameObject* _obj, int _Species, glm::vec3 _center, float _R) {
        name = "SphereCollision";
        collisionlist.push_back(this);
        gameobjct = _obj;
        //Species = _Species;
        Species = 0;
        center = _center;
        Pos = _center + gameobjct->transform.Position;
        //std::count
        R = _R;
    }
    float R;

    void update() override {
        Pos = center + gameobjct->transform.Position;
        collisions.clear();
        for (size_t i = 0; i < collisionlist.size(); i++)
        {
            if (collisionlist[i] == this) {
                continue;
            }
            switch (collisionlist[i]->Species) {
            case 0: // 球体
                if (tosphere(*dynamic_cast<SphereCollision*>(collisionlist[i]))) {
                    collisions.push_back(collisionlist[i]);
                }
                break;
            default:
                break;
            }
        }
        //std::cout << collisionlist.size();
        //std::cout << gameobjct->name;
        //std::cout << collisions.size();
        //std::cout << collisions.size();

        //if (collisions.size() != 0) {
        //    std::cout << this->gameobjct->name << "的球形碰撞检测列表" << ":";
        //    for (int i = 0; i < collisions.size(); i++) {
        //        std::cout << i << ":" << collisions[i]->gameobjct->name;
        //    }
        //
        //    std::cout << std::endl;
        //}
    }

    bool tosphere(SphereCollision& _collisions) override {
        if (_collisions.Species != 0) {
            return 0;
        }
        glm::vec3 r = _collisions.Pos - this->Pos;
        float d = r.x * r.x + r.y * r.y + r.z * r.z;
        float Rsum = _collisions.R + this->R;
        float radiusSum = Rsum * Rsum;
    
        return d <= radiusSum;
        
    }
    bool tocube(CubeCollision& _collisions) override { return 0; }
    bool tocapsule(CapsuleCollision& _collisions) override { return 0; }
    
};
void add_SphereCollision(GameObject* _obj, int _Species, glm::vec3 _center, float _R) {
    _obj->mountinglist.push_back(new SphereCollision(_obj, 0, _center, _R));
}

