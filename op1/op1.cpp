#include "openglx.h"

int main(int ai, char* ac[])
{
	//system("chcp 65001");
	PATH = ac[0];
	for (size_t i = 0; i < 3; i++)
	{
		PATH = PATH.substr(0, (PATH.find_last_of("\\")));
	}
	std::cout << PATH << std::endl;
	openginit();
	//system("chcp 65001");
	std::wcout.imbue(std::locale("zh_CN"));//wcout设置中文环境
	//const wchar_t* ch = L"控制台设置宽体中文环境，宽体中文字const wchar_t* ch";
	const wchar_t* ch = L"控制台设置宽体中文环境，宽体中文字const wchar_t* ch";
	const char8_t* cha = u8"css";
	std::wcout << ch;
	
	std::cout << ac[0];
	//std::cout << cha;
	
	rend();
	return 0;
}
