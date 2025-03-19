#include "openglx.h"

int main(int ai, char* ac[])
{
	PATH = ac[0];
	for (size_t i = 0; i < 3; i++)
	{
		PATH = PATH.substr(0, (PATH.find_last_of("\\")));
	}
	std::cout << PATH << std::endl;
	openginit();
	//system("chcp 65001");
	std::wcout.imbue(std::locale("zh_CN"));//wcout设置中文环境
	const wchar_t* ch = L"控制台设置宽体中文环境，宽体中文字const wchar_t* ch";
	std::wcout << ch;
	std::cout << ac[0];
	
	rend();
	return 0;
}
