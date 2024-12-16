#include "FST.h"
#include "Error.h"
#include <cstdlib>
#include <iomanip>
#include <vector>
#include "LT.h"
#include "IT.h"
#include <stack>



FST::RELATION::RELATION(char c, short ns)
{
	symbol = c;
	nnode = ns;
}

FST::NODE::NODE() //по умолчанию
{
	n_relation = 0;
	RELATION* relations = NULL;
};
FST::NODE::NODE(short n, RELATION rel, ...) //с параметрами
{
	n_relation = n;
	RELATION* p = &rel;
	relations = new RELATION[n];
	for (short i = 0; i < n; i++)
		relations[i] = p[i];
};
FST::FST::FST(char* s, short ns, NODE n, ...)
{
	string = s;
	nstates = ns;
	nodes = new NODE[ns];
	NODE* p = &n;
	for (int k = 0; k < ns; k++)
		nodes[k] = p[k];
	rstates = new short[nstates];
	rstates[0] = 0;
	position = -1;
};
bool step(FST::FST& fst, short*& rstates, int length) //один шаг автомата
{
	bool rc = false;
	bool contFlag = false;
	std::swap(rstates, fst.rstates); // смена массивов
	for (short i = 0; i < fst.nstates; i++) //цикл по всем состояниям
	{
		if (rstates[i] == fst.position) //если возможная позиция текущая равна текущей позиции
			for (short j = 0; j < fst.nodes[i].n_relation; j++) //до количеста инцендентных ребер
			{
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) //если нашли такой символ
				{
					if (fst.position == length)//если последний символ в строке, то ищем есть ли второй узел(второй узел для выхода)
					{
						contFlag = true;
						continue;
					}
					else
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
				};
			};
		if ((rc == false) && contFlag) //если не нашли второй узел то возвращаемся к первому
		{
			for (short j = 0; j < fst.nodes[i].n_relation; j++) //до количеста инцендентных ребер
			{
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) //если нашли такой символ
				{

					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					rc = true;
				};
			};
		}
	};
	return rc;
}
struct col
{

public:
	col(void)
	{
		column = 1;
	}
	void reset_col()
	{
		column = 1;
	}
	void set_col(int a)
	{
		column = a;
	}
	int get_col()
	{
		return column;
	}
private:
	int column;
} colum;
bool FST::execute(FST& fst) //выполнить распознование цепочки
{

	fst.rstates[0] = 0;
	fst.position = -1;
	colum.reset_col();
	short* rstates = new short[fst.nstates];//выделяем память по размеру
	memset(rstates, 0xff, sizeof(short) * fst.nstates); //инициализируем пустотой (ff)
	short lstring = strlen(fst.string); //длина цепочки
	bool rc = true;
	for (short i = 0; i < lstring && rc; i++) //по длине цепочки
	{
		fst.position++;			//продвинули позицию
		rc = step(fst, rstates, lstring); //один шаг автомата
		colum.set_col(i);
	}
	delete[] rstates;
	return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
}
