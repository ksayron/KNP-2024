#include "pch.h"
#include "framework.h"
#include <iostream>
#include <ctime>
#pragma comment(lib, "libucrt.lib")

extern "C"
{
	int __stdcall ord(char ch)
	{
		return (int)ch;
	}
	unsigned char __stdcall chr(int number)
	{
		return (unsigned char)number;
	}


	int __stdcall Compare(char* str1, char* str2)
	{
		int result = strcmp(str1, str2);
		if (result == -1)result = 2;
		return result;
	}

	int __stdcall Random(int max)
	{
		srand(time(0));
		return rand() % max + 1;
	}

	char* __stdcall Concat(char* str1, char* str2) {
		size_t totalLength = strlen(str1) + strlen(str2) + 1;

		char* result = new char[totalLength];

		size_t i = 0;
		size_t j = 0;

		while (str1[i] != '\0') {
			result[i] = str1[i];
			i++;
		}

		while (str2[j] != '\0') {
			result[i] = str2[j];
			i++;
			j++;
		}

		result[i] = '\0'; 

		return result;
	}

	char* __stdcall Copy(char* str1) {
		size_t totalLength = strlen(str1) + 1;

		char* result = new char[totalLength];

		size_t i = 0;

		while (str1[i] != '\0') {
			result[i] = str1[i];
			i++;
		}

		result[i] = '\0'; // Null-terminate the result string

		return result;
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
