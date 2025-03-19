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
    float R;//��뾶
    float l1;//������
    float l2;//������

    void update() override {
        Pos = center + gameobjct->transform.Position;
        collisions.clear();
        for (size_t i = 0; i < collisionlist.size(); i++)
        {
            if (collisionlist[i] == this) {
                continue;
            }
            switch (collisionlist[i]->Species) {
            case 2: // ������
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
        if (_collisions.Species != 2) { // ���轺����� Species Ϊ 2
            return false;
        }

        // �����������������������λ��
        glm::vec3 thisTop = this->center + glm::vec3(0.0f, l1, 0.0f);
        glm::vec3 thisBottom = this->center + glm::vec3(0.0f, l2, 0.0f);
        glm::vec3 otherTop = _collisions.center + glm::vec3(0.0f, _collisions.l1, 0.0f);
        glm::vec3 otherBottom = _collisions.center + glm::vec3(0.0f, _collisions.l2, 0.0f);

        // ��������������֮����������
        float distanceSquared = closestDistanceSquaredBetweenSegments(thisTop, thisBottom, otherTop, otherBottom);

        // �ж��Ƿ�����ײ
        float radiusSum = this->R + _collisions.R;
        float radiusSumSquared = radiusSum * radiusSum;

        return distanceSquared <= radiusSumSquared;
    }
private :
    float closestDistanceSquaredBetweenSegments(const glm::vec3& p1, const glm::vec3& q1,const glm::vec3& p2, const glm::vec3& q2){
        // ��������
        glm::vec3 d1 = q1 - p1; // ��һ���߶εķ�������
        glm::vec3 d2 = q2 - p2; // �ڶ����߶εķ�������
        glm::vec3 r = p1 - p2;   // ��һ���߶���㵽�ڶ����߶���������

        float a = glm::dot(d1, d1); // d1 �ĳ���ƽ��
        float b = glm::dot(d1, d2); // d1 �� d2 �ĵ��
        float c = glm::dot(d2, d2); // d2 �ĳ���ƽ��
        float d = glm::dot(d1, r);  // d1 �� r �ĵ��
        float e = glm::dot(d2, r);  // d2 �� r �ĵ��

        float denom = a * c - b * b; // ��ĸ

        float s, t;
        if (denom < 1e-6f) { // ��������߶�ƽ��
            s = 0.0f;
            t = e / c;
        }
        else {
            s = (b * e - c * d) / denom;
            t = (a * e - b * d) / denom;
        }

        // �� s �� t ������ [0, 1] ��Χ��
        s = glm::clamp(s, 0.0f, 1.0f);
        t = glm::clamp(t, 0.0f, 1.0f);

        // ���������
        glm::vec3 closestPoint1 = p1 + d1 * s;
        glm::vec3 closestPoint2 = p2 + d2 * t;

        // ������������ƽ��
        return glm::dot(closestPoint1 - closestPoint2, closestPoint1 - closestPoint2);
    }

};

void add_CapsuleCollision(GameObject* _obj, int _Species, glm::vec3 _center, float _l1, float _l2, float _R) {
    _obj->mountinglist.push_back(new CapsuleCollision(_obj, 2, _center, _l1, _l2, _R));
}