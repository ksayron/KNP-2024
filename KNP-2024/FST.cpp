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

FST::NODE::NODE()
{
	n_relation = 0;
	RELATION* relations = NULL;
};
FST::NODE::NODE(short n, RELATION rel, ...)
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
bool step(FST::FST& fst, short*& rstates, int length) 
{
	bool rc = false;
	bool contFlag = false;
	std::swap(rstates, fst.rstates); 
	for (short i = 0; i < fst.nstates; i++) 
	{
		if (rstates[i] == fst.position)
			for (short j = 0; j < fst.nodes[i].n_relation; j++) 
			{
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) 
				{
					if (fst.position == length)
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
		if ((rc == false) && contFlag)
		{
			for (short j = 0; j < fst.nodes[i].n_relation; j++) 
			{
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) 
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
bool FST::execute(FST& fst) 
{

	fst.rstates[0] = 0;
	fst.position = -1;
	colum.reset_col();
	short* rstates = new short[fst.nstates];
	memset(rstates, 0xff, sizeof(short) * fst.nstates); 
	short lstring = strlen(fst.string); 
	bool rc = true;
	for (short i = 0; i < lstring && rc; i++)
	{
		fst.position++;			
		rc = step(fst, rstates, lstring); 
		colum.set_col(i);
	}
	delete[] rstates;
	return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
}
