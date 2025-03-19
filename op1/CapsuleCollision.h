#pragma once
#include "collision.h"
class CapsuleCollision :
    public collision
{
public:
    CapsuleCollision(GameObject* _obj, int _Species, glm::vec3 _center, float l1 ,float l2 ,float R) {
        collisionlist.push_back(this);
        gameobjct = _obj;
        Species = _Species;
        center = _center;
        Pos = _center + gameobjct->transform.Position;
    }
    float R;//球半径
    float l1;//上球心
    float l2;//下球心

    void update() override {
        Pos = center + gameobjct->transform.Position;
        collisions.clear();
        for (size_t i = 0; i < collisionlist.size(); i++)
        {
            if (collisionlist[i] == this) {
                continue;
            }
            switch (collisionlist[i]->Species) {
            case 2: // 胶囊体
                if (tocapsule(*dynamic_cast<CapsuleCollision*>(collisionlist[i]))) {
                    collisions.push_back(collisionlist[i]);
                }
                break;
            default:
                break;
            }
        }
        
    }



    bool tosphere(SphereCollision& _collisions) override { return 0; }
    bool tocube(CubeCollision& _collisions) override { return 0; }

    bool tocapsule(CapsuleCollision &_collisions) override {
        if (_collisions.Species != 2) { // 假设胶囊体的 Species 为 2
            return false;
        }

        // 计算两个胶囊体的上下球心位置
        glm::vec3 thisTop = this->center + glm::vec3(0.0f, l1, 0.0f);
        glm::vec3 thisBottom = this->center + glm::vec3(0.0f, l2, 0.0f);
        glm::vec3 otherTop = _collisions.center + glm::vec3(0.0f, _collisions.l1, 0.0f);
        glm::vec3 otherBottom = _collisions.center + glm::vec3(0.0f, _collisions.l2, 0.0f);

        // 计算两个胶囊体之间的最近距离
        float distanceSquared = closestDistanceSquaredBetweenSegments(thisTop, thisBottom, otherTop, otherBottom);

        // 判断是否发生碰撞
        float radiusSum = this->R + _collisions.R;
        float radiusSumSquared = radiusSum * radiusSum;

        return distanceSquared <= radiusSumSquared;
    }
private :
    float closestDistanceSquaredBetweenSegments(const glm::vec3& p1, const glm::vec3& q1,const glm::vec3& p2, const glm::vec3& q2){
        // 向量计算
        glm::vec3 d1 = q1 - p1; // 第一条线段的方向向量
        glm::vec3 d2 = q2 - p2; // 第二条线段的方向向量
        glm::vec3 r = p1 - p2;   // 第一条线段起点到第二条线段起点的向量

        float a = glm::dot(d1, d1); // d1 的长度平方
        float b = glm::dot(d1, d2); // d1 和 d2 的点积
        float c = glm::dot(d2, d2); // d2 的长度平方
        float d = glm::dot(d1, r);  // d1 和 r 的点积
        float e = glm::dot(d2, r);  // d2 和 r 的点积

        float denom = a * c - b * b; // 分母

        float s, t;
        if (denom < 1e-6f) { // 如果两条线段平行
            s = 0.0f;
            t = e / c;
        }
        else {
            s = (b * e - c * d) / denom;
            t = (a * e - b * d) / denom;
        }

        // 将 s 和 t 限制在 [0, 1] 范围内
        s = glm::clamp(s, 0.0f, 1.0f);
        t = glm::clamp(t, 0.0f, 1.0f);

        // 计算最近点
        glm::vec3 closestPoint1 = p1 + d1 * s;
        glm::vec3 closestPoint2 = p2 + d2 * t;

        // 返回最近距离的平方
        return glm::dot(closestPoint1 - closestPoint2, closestPoint1 - closestPoint2);
    }

};

void add_CapsuleCollision(GameObject* _obj, int _Species, glm::vec3 _center, float _l1, float _l2, float _R) {
    _obj->mountinglist.push_back(new CapsuleCollision(_obj, 2, _center, _l1, _l2, _R));
}