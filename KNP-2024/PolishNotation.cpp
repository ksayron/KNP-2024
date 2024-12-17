
#include <stack>
#include <vector>
#include <iostream>
#include "PolishNotation.h"
#include "Error.h"

namespace PolishNotation {
	template <typename T>
	struct container : T
	{
		using T::T;
		using T::c;
	};

	std::string toString(int n) {
		char buf[40];
		sprintf_s(buf, "%d", n);
		return buf;
	}

	bool find_elem(std::stack<char> stack, size_t size, char elem) {
		for (size_t i = 0; i < size; i++)
			if (stack.top() == elem)
				return true;
			else
				stack.pop();
		return false;
	}
	int get_priority(char a)
	{
		switch (a)
		{
		case '(':
			return 0;
		case ')':
			return 0;
		case ',':
			return 1;
		case '-':
			return 2;
		case '+':
			return 2;
		case '*':
			return 3;
		case '%':
			return 3;
		case '/':
			return 3;
		case '\\':
			return 3;
		case ':':
			return 3;
		case '&':
			return 4; 
		case '|':
			return 4; 
		case '^':
			return 4; 
		default:
			return 0;
		}
	}

	void fixIt(LT::LexTable& lextable, const std::string& str, size_t length, size_t pos, const std::vector<int>& ids) {
		for (size_t i = 0, q = 0; i < str.size(); i++) {
			lextable.table[pos + i].lexema = str[i];
			if (lextable.table[pos + i].lexema == LEX_ID || lextable.table[pos + i].lexema == LEX_LITERAL) {
				lextable.table[pos + i].idxTI = ids[q];
				q++;
			}
			else
				lextable.table[pos + i].idxTI = LT_TI_NULLIDX;
		}
		int temp = str.size() + pos;
		int size = length - str.size();
		for (size_t i = 0; i < size; i++) {
			lextable.table[temp + i].idxTI = LT_TI_NULLIDX;
			lextable.table[temp + i].lexema = '';
			lextable.table[temp + i].sn = -1;
		}
	}

	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		container<std::stack<char>> stack;
		std::string PolishString;
		std::vector<int> ids;
		int operators_count = 0, operands_count = 0, iterator = 0, right_counter = 0, left_counter = 0, params_counter = 0,square_counter=0;
		bool isInv = false;
		bool isArrEl = false;

		for (int i = lextable_pos; i < lextable.size; i++, iterator++) {
			char lexem = lextable.table[i].lexema;
			char data = lextable.table[i].data;
			size_t stack_size = stack.size();
			if(lextable.table[i].idxTI!=TI_NULLIDX){
				if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F) {
					stack.push('@');
					operands_count--;
				}
			}
			switch (lexem) {
			case LEX_OPERATOR:
			{
				if (!stack.empty() && stack.top() != LEX_LEFTHESIS) {
					while (!stack.empty() && get_priority(data) <= get_priority(stack.top())) {
						PolishString += stack.top();
						stack.pop();
					}
				}
				if (data == '^')isInv = true;
				stack.push(data);
				operators_count++;
				break;
			}
			case LEX_COMMA:
			{
				while (!stack.empty()) {
					if (stack.top() == LEX_LEFTHESIS)
						break;
					PolishString += stack.top();
					stack.pop();
				}
				operands_count--;
				break;
			}
			case LEX_LEFTHESIS:
			{
				left_counter++;
				
				stack.push(lexem);
				break;
			}
			
			case LEX_RIGHTHESIS:
			{
				right_counter++;
				if (!find_elem(stack, stack_size, LEX_LEFTHESIS))
					return false;
				while (stack.top() != LEX_LEFTHESIS) {
					PolishString += stack.top();
					stack.pop();
				}
				stack.pop();
				if (!stack.empty() && stack.top() == '@') {
					PolishString += stack.top() + toString(params_counter - 1);
					params_counter = 0;
					stack.pop();
				}
				break;
			}
			case LEX_LEFT_SQUAREBRACE:
			{
				square_counter++;
				PolishString += lexem;
				isArrEl = true;
				break;
			}
			case LEX_RIGHT_SQUAREBRACE: 
			{
				square_counter--;
				PolishString += lexem;
				isArrEl = false;
				break;
			}
			case LEX_SEMICOLON:
			{
				if (operators_count != 0 && operands_count != 0)
					if ((!stack.empty() && (stack.top() == LEX_RIGHTHESIS || stack.top() == LEX_LEFTHESIS))
						|| right_counter != left_counter || (operands_count - operators_count != 1 && !isInv))
						return false;
				while (!stack.empty()) {
					PolishString += stack.top();
					stack.pop();
				}
				fixIt(lextable, PolishString, iterator, lextable_pos, ids);
				return true;
				break;
			}
			case LEX_ID: {
				if (std::find(stack.c.begin(), stack.c.begin(), '@') != stack.c.end())
					params_counter++;
				PolishString += lexem;
				if (lextable.table[i].idxTI != LT_TI_NULLIDX)
				{
					IT::Entry item = IT::GetEntry(idtable, lextable.table[i].idxTI);
					
					ids.push_back(lextable.table[i].idxTI);
				}
				if (!isArrEl) {
					operands_count++;
				}
				break;
			}
			case LEX_LITERAL: {
				if (std::find(stack.c.begin(), stack.c.begin(), '@') != stack.c.end())
				{
					params_counter++;
				}
				PolishString += lexem;
				if (lextable.table[i].idxTI != LT_TI_NULLIDX)
					ids.push_back(lextable.table[i].idxTI);
				if(!isArrEl){
					operands_count++;
				}
				break;
			}
			}

		}
		return true;
	}
	void DoPolish(LEX::LEX t) {
		for (int i = 0; i < t.lextable.size; i++)
			if (t.lextable.table[i].lexema == LEX_EQUAL)
				if (!PolishNotation(i + 1, t.lextable, t.idtable))
					throw ERROR_THROW(130);
		for (int i = 0; i < t.lextable.size; i++)
			if (t.lextable.table[i].lexema == '+' || t.lextable.table[i].lexema == '-' || t.lextable.table[i].lexema == '*' ||
				t.lextable.table[i].lexema == '/' || t.lextable.table[i].lexema == '\\' || t.lextable.table[i].lexema == ':' ||
				t.lextable.table[i].lexema == '%' || t.lextable.table[i].lexema == '&' || t.lextable.table[i].lexema == '|' || t.lextable.table[i].lexema == '^')
			{
				t.lextable.table[i].data = t.lextable.table[i].lexema;
				t.lextable.table[i].lexema = LEX_OPERATOR;
			}

	}
}