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
        std::cout << tmpJson.dump('\t');
	}

    int objsave() {

        //tmpJson["scene"]["shader"]["shader1"]["path"]["vert"] 
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

