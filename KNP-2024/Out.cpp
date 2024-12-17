#include "Parm.h"
#include "Error.h"
#include "Out.h"
#include <fstream>

#include <iostream>
#include <stdlib.h>
#include <cstdarg>
#include "time.h"

namespace Out 
{
	OUT getout(wchar_t outfile[])
	{
		OUT out;
		out.stream = new std::ofstream;
		out.stream->open(outfile);
		if (!out.stream->is_open())
			throw ERROR_THROW(112);
		wcscpy_s(out.outfile, outfile);
		return out;
	}
	void WriteLine(OUT out, const char* c, ...)
	{

		const char** temp = &c;
		while (*temp != "")
		{
			*(out.stream) << *temp;
			temp++;
		}
		*(out.stream) << *temp;
	}
	void WriteLine(OUT out, wchar_t* c, ...)
	{
		size_t   i;
		wchar_t** temp = &c;
		while (*temp != L"")
		{
			char* ttmp = new char[sizeof(*temp)];
			wcstombs_s(&i, ttmp, sizeof ttmp + 1, *temp, sizeof ttmp + 1);
			*(out.stream) << ttmp;
			temp++;
		}
	}
	void Close(OUT out)
	{
		out.stream->close();
	}
}