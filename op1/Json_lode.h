#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class Json_lode
{
public:
    Json_lode() {};
	nlohmann::json tmpJson;
	int openjson(std::string _path) {//�򿪶�ȡjson
		std::ifstream input_file(_path);
		if (!input_file.is_open()) {
			std::cerr << "�޷����ļ� data.json" << std::endl;
			return 1;
		}

		input_file >> tmpJson;
        std::cout << tmpJson.dump('\t');
	}

    int objsave() {

        //tmpJson["scene"]["shader"]["shader1"]["path"]["vert"] 
    }
	
    int outjson(std::string _path, int mode = -1) {
        try {
            std::ofstream o(_path);
            if (!o.is_open()) {
                throw std::runtime_error("�޷����ļ�: " + _path);
            }




            if (tmpJson >= 0) {
                //o << tmpJson.dump(mode);  // ������ӡ//mode*�ո�����
                o << tmpJson.dump('\t');  // ������ӡtab����
            }
            else {
                o << tmpJson;  // ���ո�ʽ
            }

            std::cout << "�ɹ����浽 " << _path << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "�������: " << e.what() << std::endl;
            throw;  // �����׳��쳣
        }
	}
};

