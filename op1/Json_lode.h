#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class Json_lode
{
public:
    Json_lode() {};
	nlohmann::json tmpJson;
	int openjson(std::string _path) {//打开读取json
		std::ifstream input_file(_path);
		if (!input_file.is_open()) {
			std::cerr << "无法打开文件 data.json" << std::endl;
			return 1;
		}

		input_file >> tmpJson;

        //shader
        //int shadernum = tmpJson["scene"]["shader"]["num"];
        //for (int i = 0; i < shadernum; i++)
        //{
        //
        //    shaderlist.push_back(new shader_a(tmpJson["scene"]["shader"][i]["name"].get<std::string>(), tmpJson["scene"]["shader"][i]["path"]["vert"].get<std::string>(), tmpJson["scene"]["shader"][i]["path"]["frag"]).get<std::string>());
        //}

        //std::cout << tmpJson.dump('\t');
        std::cout << tmpJson.dump(4);
	}

    int objsave() {
        //着色器
        std::cout << "shader save";
        tmpJson["scene"]["shader"]["num"] = shaderlist.size();
        for (int i = 0; i < shaderlist.size(); i++) {
            tmpJson["scene"]["shader"][shaderlist[i]->name]["name"] = shaderlist[i]->name;
            tmpJson["scene"]["shader"][shaderlist[i]->name]["path"]["vert"] = shaderlist[i]->vertPath;
            tmpJson["scene"]["shader"][shaderlist[i]->name]["path"]["frag"] = shaderlist[i]->fragPath;
        }
        std::cout << "shader save2";

        //动画

        for (int i = 0; i < animationslist.size(); i++)
        {
            tmpJson["scene"]["animation"][animationslist[i].name]["name"] = animationslist[i].name;
            tmpJson["scene"]["animation"][animationslist[i].name]["path"] = animationslist[i].path;
        }

        //游戏物体

        GameObject* tmpobj = &stobj;
        std::cout << "obj save";
        int num = -1;
        while (tmpobj != linknode) {
            tmpobj = tmpobj->nextOBJCT;
            num++;
        }
        tmpobj = stobj.nextOBJCT;
        std::cout << "obj save2";
        while (tmpobj != linknode) {
            if (tmpobj->tag == "UI") {
                tmpobj = tmpobj->nextOBJCT;
                continue;
            }
            num++;
            tmpJson["scene"]["gameobjct"][tmpobj->name]["tag"] = tmpobj->tag;
            tmpJson["scene"]["gameobjct"][tmpobj->name]["name"] = tmpobj->name;

            //transform
            tmpJson["scene"]["gameobjct"][tmpobj->name]["transform"]["Position"]["x"] = tmpobj->transform.Position.x;
            tmpJson["scene"]["gameobjct"][tmpobj->name]["transform"]["Position"]["y"] = tmpobj->transform.Position.y;
            tmpJson["scene"]["gameobjct"][tmpobj->name]["transform"]["Position"]["z"] = tmpobj->transform.Position.z;


            tmpJson["scene"]["gameobjct"][tmpobj->name]["transform"]["Rotate"]["x"] = tmpobj->transform.Rotate.x;
            tmpJson["scene"]["gameobjct"][tmpobj->name]["transform"]["Rotate"]["y"] = tmpobj->transform.Rotate.y;
            tmpJson["scene"]["gameobjct"][tmpobj->name]["transform"]["Rotate"]["z"] = tmpobj->transform.Rotate.z;

            tmpJson["scene"]["gameobjct"][tmpobj->name]["transform"]["Scale"]["x"] = tmpobj->transform.Scale.x;
            tmpJson["scene"]["gameobjct"][tmpobj->name]["transform"]["Scale"]["y"] = tmpobj->transform.Scale.y;
            tmpJson["scene"]["gameobjct"][tmpobj->name]["transform"]["Scale"]["z"] = tmpobj->transform.Scale.z;



            if (tmpobj->tag == "model") {
                model* tmp = dynamic_cast<model*>(tmpobj);
                tmpJson["scene"]["gameobjct"][tmpobj->name]["path"] = tmp->fpath;
            }
            int mountnum = 0;//挂载计数
            for (int i = 0; i < tmpobj->mountinglist.size(); i++)
            {
                if (tmpobj->mountinglist[i]->tag != "mesh")
                {
                    mountnum++;
                    tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmpobj->mountinglist[i]->name]["name"] = tmpobj->mountinglist[i]->name;
                    tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmpobj->mountinglist[i]->name]["tag"] = tmpobj->mountinglist[i]->tag;

                    if (tmpobj->mountinglist[i]->tag == "CubeCollision") {// 碰撞体挂载
                        CubeCollision* tmp = dynamic_cast<CubeCollision*>(tmpobj->mountinglist[i]);
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["Species"] = tmp->Species;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["center"]["x"] = tmp->center.x;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["center"]["y"] = tmp->center.y;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["center"]["z"] = tmp->center.z;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["x"] = tmp->x;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["y"] = tmp->y;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["z"] = tmp->z;
                        //int _Species, glm::vec3 _center, float _x, float _y, float _z
                    }
                    else if (tmpobj->mountinglist[i]->tag == "SphereCollision") {
                        SphereCollision* tmp = dynamic_cast<SphereCollision*>(tmpobj->mountinglist[i]);
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["Species"] = tmp->Species;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["center"]["x"] = tmp->center.x;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["center"]["y"] = tmp->center.y;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["center"]["z"] = tmp->center.z;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["R"] = tmp->R;
                    }
                    else if (tmpobj->mountinglist[i]->tag == "CapsuleCollision") {
                        CapsuleCollision* tmp = dynamic_cast<CapsuleCollision*>(tmpobj->mountinglist[i]);
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["Species"] = tmp->Species;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["center"]["x"] = tmp->center.x;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["center"]["y"] = tmp->center.y;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["center"]["z"] = tmp->center.z;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["l1"] = tmp->l1;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["l2"] = tmp->l2;
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"][tmp->name]["R"] = tmp->R;
                    }
                    else if (tmpobj->mountinglist[i]->tag == "testAnimatorCcontroller") {
                        tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"]["testAnimatorCcontroller"] = 1;
                    }
                }
            }
            tmpJson["scene"]["gameobjct"][tmpobj->name]["mounts"]["num"] = mountnum;
            tmpobj = tmpobj->nextOBJCT;
            //std::cout << "obj save3";
        }
        tmpJson["scene"]["gameobjct"]["num"] = num;

        //光照
        tmpJson["scene"]["light"]["num"] = Lightlist.LightVector.size();
        for (int i = 0; i < Lightlist.LightVector.size(); i++) {
            tmpJson["scene"]["light"][Lightlist.LightVector[i].name]["name"] = Lightlist.LightVector[i].name;
            tmpJson["scene"]["light"][Lightlist.LightVector[i].name]["mod"] = Lightlist.LightVector[i].mod;
            tmpJson["scene"]["light"][Lightlist.LightVector[i].name]["transform"]["Position"]["x"] = Lightlist.LightVector[i].transform.Position.x;
            tmpJson["scene"]["light"][Lightlist.LightVector[i].name]["transform"]["Position"]["y"] = Lightlist.LightVector[i].transform.Position.y;
            tmpJson["scene"]["light"][Lightlist.LightVector[i].name]["transform"]["Position"]["z"] = Lightlist.LightVector[i].transform.Position.z;
        }

        std::cout << tmpJson.dump('\t');
        //std::cout << tmpJson.dump(4);
        return 0;
    }
	
    int outjson(std::string _path, int mode = -1) {
        try {
            std::ofstream o(_path);
            if (!o.is_open()) {
                throw std::runtime_error("无法打开文件: " + _path);
            }

            if (tmpJson >= 0) {
                //o << tmpJson.dump(mode);  // 完美打印//mode*空格缩进
                o << tmpJson.dump('\t');  // 完美打印tab缩进
            }
            else {
                o << tmpJson;  // 紧凑格式
            }

            std::cout << "成功保存到 " << _path << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "保存错误: " << e.what() << std::endl;
            throw;  // 重新抛出异常
        }
	}
};

