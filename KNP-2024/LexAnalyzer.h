#pragma once
#include <iostream>

#include "Out.h"
#include "Log.h"
#include "In.h"
#include "IT.h"
#include "LT.h"
#include "FST.h"
void FST::LexAnalyzer(In::IN in, Out::OUT out, Log::LOG log, LT::LexTable& lextable, IT::IdTable& idtable);