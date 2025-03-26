#pragma once
#include "collision.h"

class CubeCollision :
    public collision
{
public:
    CubeCollision(GameObject* _obj, int _Species, glm::vec3 _center, float _x, float _y, float _z) {
        name = "CubeCollision";
        collisionlist.push_back(this);
        gameobjct = _obj;
        //Species = _Species;
        Species = 1;
        center = _center;
        Pos = _center + gameobjct->transform.Position;
        x = _x;
        y = _y;
        z = _z;
    }
    float x;
    float y;
    float z;
    void update() override {
        Pos = center + gameobjct->transform.Position;
        collisions.clear();
        for (size_t i = 0; i < collisionlist.size(); i++)
        {
            if (collisionlist[i] == this) {
                continue;
            }
            switch (collisionlist[i]->Species) {
            case 1: // ������
                if (tocube(*dynamic_cast<CubeCollision*>(collisionlist[i]))) {
                    collisions.push_back(collisionlist[i]);
                }
                break;
            default:
                break;
            }
        }
    }

    bool tocube(CubeCollision &_collisions) override {
        if (_collisions.Species != 1) {
            return 0;
        }
        glm::vec3 r =  _collisions.center - this->center;//�������
    
        float dx = std::abs(r.x);//���Ծ������
        float dy = std::abs(r.y);//���Ծ������
        float dz = std::abs(r.z);//���Ծ������
    
        float sumX = this->x + _collisions.x;//�߳�֮�ͼ���
        float sumY = this->y + _collisions.y;//�߳�֮�ͼ���
        float sumZ = this->z + _collisions.z;//�߳�֮�ͼ���
    
        return (dx <= sumX) && (dy <= sumY) && (dz <= sumZ);//�����������Ƿ��� x��y��z �������϶������ص���
    }
    bool tosphere(SphereCollision& _collisions) override { return 0; }
    bool tocapsule(CapsuleCollision& _collisions) override { return 0; }
};

void add_CubeCollision(GameObject* _obj, int _Species, glm::vec3 _center, float _x, float _y, float _z) {
    _obj->mountinglist.push_back(new CubeCollision(_obj, 0, _center, _x, _y, _z));
}