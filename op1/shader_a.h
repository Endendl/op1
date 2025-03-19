#pragma once
#include "opengl_shader.h"
class shader_a :
    public opengl_shader
{
public:
    shader_a(std::string _name, const char* vertexPath, const char* fragmentPath)//一种shader配一个
    {
        name = _name;
        in1t(vertexPath, fragmentPath);
    }
    void shaderload() override {//实现针对不同shader所需要的压入信息不同
        use();
        setMat4("projection", maincar->projection);
        setMat4("view", maincar->view);
        setVec3("viewPos", maincar->Position);
        int LightDirectional = 0;
        int LightPoit = 0;
        int LightSpot = 0;
        use();
        for (int i = 0; i < Lightlist.LightVector.size(); i++) {
            light* l1ght = &Lightlist.LightVector[i];
            if (l1ght->mod == light::Directional) {
                //setVec3(("lightD[" + std::to_string(LightDirectional) + "].position"), l1ght->position);//平行光用不上
                setVec3(("lightD[" + std::to_string(LightDirectional) + "].color").c_str(), l1ght->color);
                setVec3(("lightD[" + std::to_string(LightDirectional) + "].dirToLight").c_str(), l1ght->direction);
                //std::cout << l1ght->direction.x << " " << l1ght->direction.y << " " << l1ght->direction.z << std::endl;
                //setVec3("lightD.dirToLight", l1ght->direction);
                LightDirectional++;
            }
            else if (l1ght->mod == light::Point) {
                setVec3(("lightP[" + std::to_string(LightPoit) + "].position").c_str(), l1ght->position);
                setVec3(("lightP[" + std::to_string(LightPoit) + "].color").c_str(), l1ght->color);
                setFloat(("lightP[" + std::to_string(LightPoit) + "].constant").c_str(), l1ght->constant);
                setFloat(("lightP[" + std::to_string(LightPoit) + "].linear").c_str(), l1ght->linear);
                setFloat(("lightP[" + std::to_string(LightPoit) + "].quadratic").c_str(), l1ght->quadratic);
                LightPoit++;
            }
            else if (l1ght->mod == light::Spot) {
                setVec3("lightS[" + std::to_string(LightSpot) + "].position", l1ght->position);
                setVec3("lightS[" + std::to_string(LightSpot) + "].color", l1ght->color);

                setVec3("lightS[" + std::to_string(LightSpot) + "].dirToLight", l1ght->direction);

                setFloat("lightS[" + std::to_string(LightSpot) + "].constant", l1ght->constant);
                setFloat("lightS[" + std::to_string(LightSpot) + "].linear", l1ght->linear);
                setFloat("lightS[" + std::to_string(LightSpot) + "].quadratic", l1ght->quadratic);
                setFloat("lightS[" + std::to_string(LightSpot) + "].CosPhyInner", l1ght->CosPhyInner);
                setFloat("lightS[" + std::to_string(LightSpot) + "].CosPhyOutter", l1ght->CosPhyOutter);
                LightSpot++;
            }
        }
        setInt("LightDirectionalNumber", LightDirectional);
        setInt("LightPoitNumber", LightPoit);
        setInt("LightSpotNumber", LightSpot);
        //std::cout << "LightDirectionalNumber：" << LightDirectional << "\tLightPoitNumber：" << LightPoit << "\tLightSpotNumber：" << LightSpot<<std::endl;
    }
};

