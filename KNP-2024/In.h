#pragma once
#include "LT.h"
#define IN_MAX_LEN_TEXT 1024*1024 //макс размер исходного кода 1 мб
#define IN_CODE_ENDL '\n' //символ конца строки
#define DIVIDE ';' //разделитель
#define MAX_LEXEM_LENGTH 16 //максимальная длина лексемы
#include <list>
//таблица проверки входной информации, индекс = код(Windows-1251) символа//значения IN::F - запрещенный символ, IN::T - разрешенный символ, IN::I - игнорировать(не вводить),// если 0Б= значение 256 - то вводится данное значение
#define IN_CODE_TABLE {\
IN::T,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::S,/*tabulation*/\
IN::N,/*New line*/\
IN::F,/**/\
IN::F,/**/\
IN::T,/*carrege return*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/*left-arrow*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::S,/*Space*/\
IN::L,/*!*/\
IN::D,/*"*/\
IN::I,/*#*/\
IN::F,/*$*/\
IN::L,/*%*/\
IN::L,/*&*/\
IN::C,/*'*/\
IN::L,/*(*/\
IN::L,/*)*/\
IN::L,/***/\
IN::L,/*+*/\
IN::L,/*,*/\
IN::L,/*-*/\
IN::F,/*.*/\
IN::L,/*/*/\
IN::T,/*0*/\
IN::T,/*1*/\
IN::T,/*2*/\
IN::T,/*3*/\
IN::T,/*4*/\
IN::T,/*5*/\
IN::T,/*6*/\
IN::T,/*7*/\
IN::T,/*8*/\
IN::T,/*9*/\
IN::L,/*:*/\
IN::L,/*;*/\
IN::L,/*<*/\
IN::L,/*=*/\
IN::L,/*>*/\
IN::F,/*?*/\
IN::F,/*@*/\
IN::T,/*A*/\
IN::T,/*B*/\
IN::T,/*C*/\
IN::T,/*D*/\
IN::T,/*E*/\
IN::T,/*F*/\
IN::T,/*G*/\
IN::T,/*H*/\
IN::T,/*I*/\
IN::T,/*J*/\
IN::T,/*K*/\
IN::T,/*L*/\
IN::T,/*M*/\
IN::T,/*N*/\
IN::T,/*O*/\
IN::T,/*P*/\
IN::T,/*Q*/\
IN::T,/*R*/\
IN::T,/*S*/\
IN::T,/*T*/\
IN::T,/*U*/\
IN::T,/*V*/\
IN::T,/*W*/\
IN::T,/*X*/\
IN::T,/*Y*/\
IN::T,/*Z*/\
IN::L,/*[*/\
IN::L,/*\*/\
IN::L,/*]*/\
IN::L,/*^*/\
IN::T,/*_*/\
IN::F,/*`*/\
IN::T,/*a*/\
IN::T,/*b*/\
IN::T,/*c*/\
IN::T,/*d*/\
IN::T,/*e*/\
IN::T,/*f*/\
IN::T,/*g*/\
IN::T,/*h*/\
IN::T,/*i*/\
IN::T,/*j*/\
IN::T,/*k*/\
IN::T,/*l*/\
IN::T,/*m*/\
IN::T,/*n*/\
IN::T,/*o*/\
IN::T,/*p*/\
IN::T,/*q*/\
IN::T,/*r*/\
IN::T,/*s*/\
IN::T,/*t*/\
IN::T,/*u*/\
IN::T,/*v*/\
IN::T,/*w*/\
IN::T,/*x*/\
IN::T,/*y*/\
IN::T,/*z*/\
IN::L,/*{*/\
IN::F,/*|*/\
IN::L,/*}*/\
IN::F,/*~*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/* */\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/*¤*/\
IN::F,/**/\
IN::F,/*¦*/\
IN::F,/*§*/\
IN::F,/**/\
IN::F,/*©*/\
IN::F,/**/\
IN::F,/*«*/\
IN::F,/*¬*/\
IN::F,/*­*/\
IN::F,/*®*/\
IN::F,/**/\
IN::F,/*°*/\
IN::F,/*±*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/*µ*/\
IN::F,/*¶*/\
IN::F,/*·*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/*»*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
}


namespace In
{
	struct lexem
	{
		int line;
		int col;
		unsigned char* lexem;
	};

	struct IN //исходные данные
	{
		//D = double comma O - octotorp, comment
		enum { T = 1024, F = 2048, L = 256, C = 128, N = 64, D = 32, I = 16, S = 0 }; //S - space t - допустимый символ F- недопустимый, C-comma, L - Single lexem
		int size;		//размер исходного кода
		int lines;		//количество строк
		int ignor;		//кол-во проигнорированных символов
		//unsigned char* text;		
		//int code[256];		//таблица проверки T, F, I новое значение

		std::list<lexem> lexems;//Исходный код (Windows - 1251)

	};

	IN getin(wchar_t infile[]);  //ввести и проверить входной поток
}