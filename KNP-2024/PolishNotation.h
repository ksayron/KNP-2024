#pragma once
#include "LEX.h"

namespace PolishNotation {
	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
	void DoPolish(LEX::LEX t);
}