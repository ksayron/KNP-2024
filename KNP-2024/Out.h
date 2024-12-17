#pragma once
#include <fstream>
#include "Parm.h"
#include "Error.h"
namespace Out 
{
	struct OUT
	{
		wchar_t outfile[PARM_MAX_SIZE]; 
		std::ofstream* stream;			
	};

	static const OUT INITOUT = { L"",NULL };		
	OUT getout(wchar_t outfile[]);					
	void WriteLine(OUT out, const char* c, ...);
	void WriteLine(OUT out, wchar_t* c, ...); 
	void Close(OUT out); 
}
