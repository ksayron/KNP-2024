#include "pch.h"
#include "framework.h"
#include <iostream>
#include <ctime>
#pragma warning(disable: 4996)

extern "C"
{
	int __stdcall ctn(char ch)
	{
		if (ch >= '0' && ch <= '9')		return (int)ch - 48;
		else return 0;
	}
	unsigned char __stdcall ntc(int number)
	{
		if (number < 0)number *= -1;
		if (number > 9)number %= 10;
		return (char)number;
	}


	int __stdcall Compare(char* str1, char* str2)
	{
		int result = strcmp(str1, str2);
		if (result == -1)result = 2;
		return result;
	}

	int __stdcall GetSize(char* str1)
	{
		return strlen(str1);
	}

	int __stdcall Random(int max)
	{
		srand(time(0));
		return rand() % max + 1;
	}

	char* __stdcall Copy(char* str1) {

		return str1;
	}

	void __stdcall outputuint(int a)
	{
		std::cout << a << std::endl;
	}
	void __stdcall outputchar(char a)
	{
		std::cout << a << std::endl;
	}
	void __stdcall outputstr(void* in)
	{
		char* a = (char*)in;
		setlocale(0, "");
		if (a != NULL)
			std::cout << a << std::endl;
	}

}
