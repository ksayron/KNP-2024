#include "IT.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstdarg>
#include "Error.h"



namespace IT
{
	IdTable Create(	
		int size	
	) {
		if (size > TI_MAXSIZE)
		{
			throw ERROR_THROW(130);
		}
		IdTable out;
		out.maxsize = size;
		out.size = 0;
		out.table = new Entry[size];
		return out;
	};
	void Add(
		IdTable& idtable,	
		Entry entry			
	) {
		if (idtable.size + 1 > idtable.maxsize)
			throw ERROR_THROW(133);
		idtable.table[idtable.size++] = entry;
		//add error maxsize
	};
	Entry GetEntry(	
		IdTable& idtable,	
		int n				
	) {
		if (idtable.size + 1 > idtable.maxsize)
			throw ERROR_THROW(134);
		//add error with n
		return idtable.table[n];
	};
	int IsId(
		IdTable& idtable,	
		char id[ID_MAXSIZE] 
	) {
		bool bflag = false;
		for (int i = 0; i < idtable.size; i++)
		{
			if (strlen(id) != strlen(idtable.table[i].id))
				continue;
			for (int j = 0; j < strlen(id); j++)
			{
				if (idtable.table[i].id[j] != id[j])
				{
					bflag = false;
					break;
				}
				else {
					bflag = true;
				}
			}
			if (bflag)
				return i;
		}
		return TI_NULLIDX;
	};
	int IsLX(
		IdTable& idtable,	
		IDDATATYPE type,
		int data
	) {

		if(type == IT::INT){
			for (int i = 0; i < idtable.size; i++)
			{
				if (idtable.table[i].idtype != IT::L || idtable.table[i].iddatatype != type
					||
					data != idtable.table[i].value.vint)
					continue;
				else
					return i;
			}
		}
		if(type==IT::ARR){
			for (int i = 0; i < idtable.size; i++)
			{
				if (idtable.table[i].idtype != IT::L || idtable.table[i].iddatatype != type
					||
					data != idtable.table[i].value.vstr.len)
					continue;
				else
					return i;
			}
		}
		return TI_NULLIDX;
	};
	int IsLX(
		IdTable& idtable,	
		IDDATATYPE type,
		char data
	) {
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].iddatatype != type
				||
				data != idtable.table[i].value.vchar)
				continue;
			else
				return i;
		}
		return TI_NULLIDX;
	};
	int IsLX(
		IdTable& idtable,	
		IDDATATYPE type,
		char* data
	) {
		int len = 0;
		while (true) {
			if (data[len] == '\0')
				break;
			else
				len++;
		}
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].iddatatype != type)
				continue;
			if (len != idtable.table[i].value.vstr.len)
				continue;
			else
			{
				bool f = false;
				for (int j = 0; j < len; j++) {
					if (idtable.table[i].value.vstr.str[j] != data[j])
					{
						f = false;
						break;
					}
					else
						f = true;

				}
				if (f)
					return i;
			}

		}
		return TI_NULLIDX;
	};





	bool isUniq(
		IdTable& idtable,	
		char id[ID_MAXSIZE] 
	) {
		bool bflag = false;
		int isQ = 0;
		for (int i = 0; i < idtable.size; i++)
		{
			if (strlen(id) != strlen(idtable.table[i].id))
				continue;
			for (int j = 0; j < strlen(id); j++)
			{
				if (idtable.table[i].id[j] != id[j])
				{
					bflag = false;
					break;
				}
				else {
					bflag = true;
				}
			}
			if (bflag)
				isQ++;
		}
		return isQ == 1;
	};


	void Delete(IdTable& idtable) {
		delete& idtable;
	};

}