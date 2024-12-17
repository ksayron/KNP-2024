#pragma once
#include "Semantic.h"
namespace Semantic {
	void doAnalyse(LEX::LEX t) {
		operands(t);
		parameters(t);
		returns(t);

	};

	void operands(LEX::LEX t) {
		for (int i = 0; i < t.lextable.size; i++) {
			if (t.lextable.table[i].lexema == LEX_OPERATOR)
			{
				switch (t.lextable.table[i].data)
				{
				case '=':
				{
					int pos = -1;
					if (t.lextable.table[i + pos].lexema == ']') {
						pos = -4;
					}
					int datatype = -1;
					while (t.lextable.table[i + pos].lexema != LEX_SEMICOLON) {
						if ((t.lextable.table[i + pos].lexema == LEX_LITERAL || t.lextable.table[i + pos].lexema == LEX_ID)&& t.lextable.table[i + pos-1].lexema!='[')
						{
							if (datatype == -1)
							{
								datatype = t.idtable.table[t.lextable.table[i + pos].idxTI].iddatatype;
							}
							else
							{
								if (datatype != t.idtable.table[t.lextable.table[i + pos].idxTI].iddatatype)
								{
									if (!((datatype == IT::INT && t.idtable.table[t.lextable.table[i + pos].idxTI].iddatatype == IT::ARR) || (datatype == IT::ARR && t.idtable.table[t.lextable.table[i + pos].idxTI].iddatatype == IT::INT))) {
										throw ERROR_THROW_IN(704, t.lextable.table[i + pos].sn, t.lextable.table[i + pos].cn)
									}
								}
							}

									
							if (t.idtable.table[t.lextable.table[i + pos].idxTI].idtype == IT::F) {
								while (t.lextable.table[i + pos].lexema != LEX_RIGHTHESIS)
									pos++;
							}
						}
						if (datatype == IT::STR && t.lextable.table[i + pos].lexema == LEX_OPERATOR && pos != 0 && t.lextable.table[i + pos].data != '+') {
							throw ERROR_THROW_IN(708, t.lextable.table[i + pos].sn, t.lextable.table[i + pos].cn)
						}
						if (datatype == IT::CHR && t.lextable.table[i + pos].lexema == LEX_OPERATOR && pos != 0 && t.lextable.table[i + pos].data != '+' && t.lextable.table[i + pos].data != '-') {
							throw ERROR_THROW_IN(710, t.lextable.table[i + pos].sn, t.lextable.table[i + pos].cn)
						}
						pos++;
					}
					i += pos - 1;
					break;
				}
				}
			}
			
			if (t.lextable.table[i].lexema == LEX_UNTIL) {
				int pos = 2;
				while (true) {
					if (t.lextable.table[i + pos].lexema == LEX_LITERAL || t.lextable.table[i + pos].lexema == LEX_ID)
					{
						if (t.idtable.table[t.lextable.table[i + pos].idxTI].iddatatype == IT::STR)
							throw ERROR_THROW_IN(709, t.lextable.table[i + pos].sn, t.lextable.table[i + pos].cn)
					}
					pos++;
					if (t.lextable.table[i + pos].lexema == LEX_RIGHTHESIS || pos > 6)
						break;
				}
			}
		}
	}

	void parameters(LEX::LEX t) {
		for (int i = 0; i < t.lextable.size; i++) {
			if (t.lextable.table[i].lexema == LEX_PRINT && t.idtable.table[t.lextable.table[i + 1].idxTI].idtype == IT::F)
				throw ERROR_THROW_IN(701, t.lextable.table[i + 1].sn, t.lextable.table[i + 1].cn)
				if (t.lextable.table[i].lexema == LEX_ID && t.idtable.table[t.lextable.table[i].idxTI].idtype == IT::F && t.lextable.table[i - 3].lexema != LEX_EXPORT && t.lextable.table[i - 3].lexema != LEX_DECLARE)
				{
					short* types = new short[256];
					int typesLen = 0;
					
					int funcDeclarePos = t.idtable.table[t.lextable.table[i].idxTI].idxfirstLE;
					while (t.lextable.table[++funcDeclarePos].lexema != LEX_RIGHTHESIS)
					{
						if (t.lextable.table[funcDeclarePos].lexema == LEX_ID || t.lextable.table[funcDeclarePos].lexema == LEX_LITERAL)
							types[typesLen++] = t.idtable.table[t.lextable.table[funcDeclarePos].idxTI].iddatatype;
					}
					int pos = 1;
					int paramCount = 0;
					while (t.lextable.table[i + pos].lexema != LEX_RIGHTHESIS) {
						if (t.lextable.table[i + pos].lexema == LEX_ID || t.lextable.table[i + pos].lexema == LEX_LITERAL)
							if (t.idtable.table[t.lextable.table[i + pos].idxTI].iddatatype != types[paramCount++])
								throw ERROR_THROW_IN(703, t.lextable.table[i + pos].sn, t.lextable.table[i + pos].cn)
								pos++;
					}
					if (paramCount != typesLen)
						throw ERROR_THROW_IN(702, t.lextable.table[i + pos].sn, t.lextable.table[i + pos].cn)
						i += pos;
				}
		}
	}


	
	void returns(LEX::LEX t) {
		for (int i = 0; i < t.lextable.size; i++) {
			if (t.lextable.table[i].lexema == LEX_ID && t.idtable.table[t.lextable.table[i].idxTI].idtype == IT::F && t.lextable.table[i - 3].lexema == LEX_DECLARE)
			{
				int pos = 1;
				short retType = t.idtable.table[t.lextable.table[i].idxTI].iddatatype;
				while (t.lextable.table[i + pos].lexema != LEX_RETURN) {
					pos++;
				}
				pos++;
				if ((t.lextable.table[i + pos].lexema == LEX_ID || t.lextable.table[i + pos].lexema == LEX_LITERAL) && t.idtable.table[t.lextable.table[i + pos].idxTI].idtype != IT::F && (short)t.idtable.table[t.lextable.table[i + pos].idxTI].iddatatype != retType)
					throw ERROR_THROW_IN(701, t.lextable.table[i + pos].sn, t.lextable.table[i + pos].cn)
			}
		}
	}
}
