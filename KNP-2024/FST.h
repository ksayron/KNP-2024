#pragma once
#include <iostream>

#include "Out.h"
#include "Log.h"
#include "In.h"
#include "IT.h"
#include "LT.h"
namespace FST
{
	struct RELATION
	{
		char symbol; 
		short nnode; 
		RELATION(
			char c = 0x00, 
			short ns = NULL
		);
	};
	struct NODE
	{
		short n_relation;	
		RELATION* relations;
		NODE();
		NODE(
			short n,		
			RELATION rel, ... 
		);
	};
	struct FST	
	{
		char* string; 
		short position; 
		short nstates; 
		NODE* nodes;	
		short* rstates; 
		FST(
			char* s, 
			short ns, 
			NODE n, ...	
		);

	};
	bool execute(FST& fst); 
	void LexAnalyzer(In::IN in, Out::OUT out, Log::LOG log, LT::LexTable& a, IT::IdTable& b); 
	struct libfuncs { 
	std::string name;
	IT::IDDATATYPE params[255];
	int parcount = 0;
	IT::IDDATATYPE retval;
	};

	struct Checker {
		FST* chain;
		IT::IDDATATYPE iddatatype;

		char lexName;
		Checker(FST* f, char c, IT::IDDATATYPE t) {
			chain = f;
			lexName = c;
			iddatatype = t;
		}
	};

}

