#include "Parm.h"
#include "Error.h"
#include "Log.h"
#include "In.h"
#include <fstream>
#pragma warning (disable : 4996)
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <cstdarg>
#include "time.h"

namespace Log //работа с протоколом
{
	LOG getlog(wchar_t logfile[])
	{
		LOG out;
		out.stream = new std::ofstream;
		out.stream->open(logfile);
		if (!out.stream->is_open())
			throw ERROR_THROW(112);
		wcscpy_s(out.logfile, logfile);
		return out;
	}
	void WriteLine(LOG log, const char* c, ...)
	{
		const char** temp = &c;
		while (*temp != "")
		{
			*(log.stream) << *temp;
			temp++;
		}
		*(log.stream) << std::endl;
	}


	void WriteLog(LOG log)
	{
		*(log.stream) << "---- Protocol -----\n\tDate: ";
		time_t time_sec = time(NULL);
		tm time_date;
		localtime_s(&time_date, &time_sec);
		(time_date.tm_mday < 10) ? (*(log.stream) << '0' << time_date.tm_mday << '.') : (*(log.stream) << time_date.tm_mday << '.');
		(time_date.tm_mon + 1 > 9) ? (*(log.stream) << time_date.tm_mon + 1 << '.') : (*(log.stream) << '0' << time_date.tm_mon + 1 << '.');
		*(log.stream) << time_date.tm_year + 1900 << ' ';
		(time_date.tm_hour > 9) ? (*(log.stream) << time_date.tm_hour << ':') : (*(log.stream) << '0' << time_date.tm_hour << ':');
		(time_date.tm_min > 9) ? (*(log.stream) << time_date.tm_min << ':') : (*(log.stream) << '0' << time_date.tm_min << ':');
		(time_date.tm_sec > 9) ? (*(log.stream) << time_date.tm_sec << ':') : (*(log.stream) << '0' << time_date.tm_sec << ':');
		*(log.stream) << "------------\n";

	}
	void WriteParm(LOG log, Parm::PARM parm)
	{


		*log.stream << "---- Params----\n";

		int i = 0;
		char ch;
		*log.stream << "-log: ";
		while ((ch = wctob(parm.log[i++])) != EOF)
			*log.stream << ch;
		i = 0;
		*log.stream << "\n-out: ";
		while ((ch = wctob(parm.out[i++])) != EOF)
			*log.stream << ch;
		i = 0;
		*log.stream << "\n-in: ";
		while ((ch = wctob(parm.in[i++])) != EOF)
			*log.stream << ch;
		*(log.stream) << std::endl;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*(log.stream) << "---- Input data ------\n";
		*(log.stream) << "Num of symbols: " << in.size;
		*(log.stream) << "\nNum of lexs: " << in.lexems.size();
		*(log.stream) << "\nNum of lines: " << in.lines << std::endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{

		std::cout << "Error " << error.id << ": " << error.message;
		if (error.inext.col != -1 && error.inext.line != -1)
			std::cout << ", line " << error.inext.line << ", column " << error.inext.col << std::endl;

		if (log.stream != NULL)
		{
			*log.stream << "\nError " << error.id << ": " << error.message;
			if (error.inext.col != -1 && error.inext.line != -1)
				*(log.stream) << ", line " << error.inext.line << ", column " << error.inext.col << std::endl;
			else
				*(log.stream) << std::endl;
		}


	}

	void LogTables(LOG log, LEX::LEX t) {

		*log.stream << std::setw(9 + 12 + 12 + 15 + 25) << std::left << "--------Lexem table--------" << std::endl;
		*log.stream << std::setw(9) << std::left << "Positiob"
			<< std::setw(12) << std::left << "№ line"
			<< std::setw(12) << std::left << "№ column"
			<< std::setw(15) << std::left << "Lexem"
			<< std::setw(25) << std::left << "Id table identificators"
			<< std::endl;
		std::cout << std::setw(9 + 12 + 12 + 15 + 25) << std::left << "--------Таблица лексем--------" << std::endl;
		std::cout << std::setw(9) << std::left << "Позиция"
			<< std::setw(12) << std::left << "№ строки"
			<< std::setw(12) << std::left << "№ столбца"
			<< std::setw(15) << std::left << "Лексема"
			<< std::setw(25) << std::left << "Индекс таблицы идентификаторов"
			<< std::endl;

		for (int i = 0; i < t.lextable.size; i++)
		{
			LT::Entry a = LT::GetEntry(t.lextable, i);
			*log.stream << std::setw(9) << std::left << i
				<< std::setw(12) << std::left << a.sn
				<< std::setw(12) << std::left << a.cn
				<< std::setw(15) << std::left << a.lexema
				<< std::setw(25) << std::left << a.idxTI
				<< std::endl;
			std::cout << std::setw(9) << std::left << i
				<< std::setw(12) << std::left << a.sn
				<< std::setw(12) << std::left << a.cn
				<< std::setw(15) << std::left << a.lexema
				<< std::setw(25) << std::left << a.idxTI
				<< std::endl;
		}
	}
	void LogIDTables(LOG log, LEX::LEX t) {

		*log.stream << std::setw(9 + 16 + 15 + 15 + 15) << std::left << "\n\n--------ID Table--------" << std::endl;
		*log.stream << std::setw(9) << std::left << "Position"
			<< std::setw(16) << std::left << "Name"
			<< std::setw(15) << std::left << "Type"
			<< std::setw(15) << std::left << "Data type"
			<< std::setw(15) << std::left << "Value"
			<< std::endl;
		std::cout << std::setw(9 + 16 + 15 + 15 + 15) << std::left << "\n\n--------Таблица идентификаторов--------" << std::endl;
		std::cout << std::setw(9) << std::left << "Позиция"
			<< std::setw(16) << std::left << "Имя"
			<< std::setw(15) << std::left << "Вид"
			<< std::setw(15) << std::left << "Тип данных"
			<< std::setw(15) << std::left << "Значение"
			<< std::endl;
		for (int i = 0; i < t.idtable.size; i++)
		{

			std::string type, datatype, data;
			IT::Entry b = IT::GetEntry(t.idtable, i);
			char* buff;
			switch (b.idtype) {
			case IT::V:
				type = "Variable";
				break;
			case IT::F:
				type = "Action";
				break;
			case IT::L:
				type = "Literal";
				break;
			case IT::P:
				type = "Param";
				break;
			}
			switch (b.iddatatype) {
			case IT::INT:
				datatype = "Number";
				buff = new char[100];
				_itoa(b.value.vint, buff, 10);
				data = buff;
				delete[]buff;
				break;
			case IT::STR:
				datatype = "String";
				if (b.value.vstr.len == 0)
					data = "*empty string*";
				else
					data = b.value.vstr.str;
				break;

			case IT::CHR:
				datatype = "Symbol";
				data = b.value.vchar;
				break;
			case IT::ARR:
				datatype = "Array";
				buff = new char[10];
				_itoa(b.value.varr.len, buff, 10);
				data = buff;
				delete[]buff;
				break;

			}


			*log.stream << std::setw(9) << std::left << i
				<< std::setw(16) << std::left << b.id
				<< std::setw(15) << std::left << type
				<< std::setw(15) << std::left << datatype
				<< std::setw(15) << std::left << data
				<< std::endl;
			std::cout << std::setw(9) << std::left << i
				<< std::setw(16) << std::left << b.id
				<< std::setw(15) << std::left << type
				<< std::setw(15) << std::left << datatype
				<< std::setw(15) << std::left << data
				<< std::endl;
		}
	}

	void Close(LOG log)
	{
		log.stream->close();
	}
}