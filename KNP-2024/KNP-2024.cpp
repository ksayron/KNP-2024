#include "tchar.h"
#include <iostream>
#include <locale>
#include <cwchar>
#include "MFST.h"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "FST.h"
#include "LexAnalyzer.h"
#include "IT.h"
#include "Semantic.h"
#include "PolishNotation.h"
#include "CodeGeneration.h"
#include "CodeExectution.h"






int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	Log::LOG log = Log::INITLOG;
	Out::OUT out = Out::INITOUT;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv); // получение параметров командной строки
		log = Log::getlog(parm.log); // получение лога
		out = Out::getout(parm.out); // получение файла вывода
		Log::WriteParm(log, parm); // запись параметров в лог
		Log::WriteLog(log); // запись лога
		In::IN in = In::getin(parm.in); // получение входного файла
		Log::WriteIn(log, in); // запись входного файла в лог

		LEX::LEX tables(LT::Create(in.lexems.size()), IT::Create(in.lexems.size())); // создание таблиц лексем и идентификаторов

		Log::WriteLine(log, "--------Начало лексического анализа--------", "");
		// лексический анализатор
		FST::LexAnalyzer(in, out, log, tables.lextable, tables.idtable);

		if (parm.showTables) {
			Log::LogTables(log, tables);
		}// вывод таблиц в лог
		if (parm.showITables) {
			Log::LogIDTables(log, tables);
		} // вывод таблиц идентификаторов в лог
		Log::WriteLine(log, "--------Конец лексического анализа--------", "");

		Log::WriteLine(log, "--------Начало синтаксического анализа--------", "");
		if (parm.showMfst) {
			MFST_TRACE_START(log);
		}
		MFST::Mfst mfst(tables, GRB::getGreibach(), parm.showMfst);
		if (!mfst.start(log))
		{
			throw ERROR_THROW(600);
		}
		mfst.savededucation();
		if(parm.showMfst){
			mfst.printrules(log);
		}
		Log::WriteLine(log, "--------Конец синтаксического анализа--------", "");

		Log::WriteLine(log, "--------Начало семантического анализа--------", "");
		//семантический анализ
		Semantic::doAnalyse(tables);
		Log::WriteLine(log, "--------Конец семантического анализа--------", "");

		//польская запись
		PolishNotation::DoPolish(tables);

		Log::WriteLine(log, "--------Все анализаторы отработали без ошибок--------", "");

		//генерация кода
		CG::Generate(tables, out);
		Log::WriteLine(log, "--------Код успешно сгенерирован--------", "");


		Execute(parm.out);

	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	Log::Close(log);
}