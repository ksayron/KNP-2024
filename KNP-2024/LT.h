#pragma once
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0XFFFFFFFF
#define LEX_NUM 't'
#define LEX_STRING	't'
#define LEX_CHAR	't' 
#define LEX_TYPE	't' 
#define LEX_ARRAY	'a'
#define LEX_ID		'i'
#define LEX_UNTIL	'u'
#define LEX_IF		'o'
#define LEX_MAIN	'm'
#define LEX_LITERAL	'l'
#define LEX_FUNCTION 'f'
#define LEX_DECLARE	'd'
#define LEX_RETURN	'r'
#define LEX_EXPORT	'e'
#define LEX_PRINT	'p'
#define LEX_SEMICOLON ';'
#define LEX_COMMA	','
#define LEX_LEFTBRACE '{'
#define LEX_RIGHTBRACE	'}'

#define LEX_LEFT_SQUAREBRACE '['
#define LEX_RIGHT_SQUAREBRACE	']'

#define LEX_LEFTHESIS	'('
#define LEX_RIGHTHESIS	')'
#define LEX_PLUS		'v'
#define LEX_AND			'v'
#define LEX_OR			'v'
#define LEX_INVERSE		'v'
#define LEX_MINUS		'v'
#define LEX_STAR		'v'
#define LEX_DIRSLASH	'v'
#define LEX_EQUAL		'v'
#define LEX_OPERATOR	'v'
#define LEX_BOOL_OPERATOR 'b'
#define EMPTY_DATA		'\0'

namespace LT
{
	struct Entry
	{
		char lexema;
		int sn;
		int cn;
		int idxTI;
		char data;

		Entry(
			char lexema,
			int sn,
			int cn,
			int idxTI,
			char symbol = EMPTY_DATA
		) {
			this->lexema = lexema;
			this->sn = sn;
			this->cn = cn;
			this->idxTI = idxTI;
			this->data = data;
		};

		Entry() = default;
	};
	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};
	LexTable Create(
		int size
	);
	void Add(
		LexTable& lextable,
		Entry entry
	);
	Entry GetEntry(
		LexTable& lextable,
		int n
	);


	void Delete(LexTable& lextable);
}