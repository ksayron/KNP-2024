#include "Error.h"
#include "In.h"
#include <fstream>
#include "FST.h"

namespace In
{
	IN getin(wchar_t infile[])
	{
		IN out;
		out.lines = 1;
		out.size = 0;
		out.ignor = 0;
		std::ifstream file(infile);
		if (!file)
			throw ERROR_THROW(110)//файл не открыт
		else
		{
			unsigned int chars[] = IN_CODE_TABLE;
			file >> std::noskipws;
			file.seekg(0, std::ios_base::end);
			int size = file.tellg();
			file.seekg(0, std::ios_base::beg);
			if (size > IN_MAX_LEN_TEXT)
				throw ERROR_THROW(112)
				unsigned char tmp;
			int line_counter = 0; 
			lexem currentLex;
			unsigned char* lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
			int lexContainerLen = 0;
			bool IsPris = false;

			while (file >> tmp)
			{
				switch (chars[(int)tmp])
				{
				case IN::T:
				{
					line_counter++;
					out.size++;
					if (lexContainerLen == 0) {
						currentLex.line = out.lines;
						currentLex.col = line_counter;
					}
					if (lexContainerLen >= MAX_LEXEM_LENGTH - 1)
						throw ERROR_THROW_IN(113, out.lines, line_counter);
					lexContainer[lexContainerLen++] = tmp;
					break;
				}
				case IN::C: 
				{
					line_counter++;
					out.size++;
					char data, commaAgain;
					file >> data;
					line_counter++;
					out.size++;
					if (!data)
						throw ERROR_THROW_IN(114, out.lines, line_counter)
						file >> commaAgain;
					line_counter++;
					out.size++;
					if (!commaAgain || commaAgain != '\'')
						throw ERROR_THROW_IN(114, out.lines, line_counter)

						if (lexContainerLen != 0) {
							lexContainer[lexContainerLen++] = '\0';
							currentLex.lexem = new unsigned char[lexContainerLen];
							for (int i = 0; i < lexContainerLen; i++)
								currentLex.lexem[i] = lexContainer[i];
							out.lexems.push_back(currentLex);
							delete[]lexContainer;
							lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
							lexContainerLen = 0;
						}

					if (lexContainerLen == 0) {
						currentLex.line = out.lines;
						currentLex.col = line_counter;
					}
					currentLex.lexem = new unsigned char[lexContainerLen];
					currentLex.lexem[0] = '\'';
					currentLex.lexem[1] = data;
					currentLex.lexem[2] = '\'';
					currentLex.lexem[3] = '\0';
					out.lexems.push_back(currentLex);

					if (lexContainerLen > MAX_LEXEM_LENGTH)
						throw ERROR_THROW_IN(113, out.lines, line_counter);
					break;
				}
				case IN::D:
				{
					if (lexContainerLen != 0) {
						lexContainer[lexContainerLen++] = '\0';
						currentLex.lexem = new unsigned char[lexContainerLen];
						for (int i = 0; i < lexContainerLen; i++)
							currentLex.lexem[i] = lexContainer[i];
						out.lexems.push_back(currentLex);
						delete[]lexContainer;
						lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
						lexContainerLen = 0;
					}

					line_counter++;
					out.size++;
					int pos = 0;
					char* data = new char[TI_STR_MAXSIZE];
					data[0] = '\"';
					char t;
					do {
						file >> t;
						pos++;
						line_counter++;
						out.size++;
						if (pos - 1 > TI_STR_MAXSIZE)
							throw ERROR_THROW_IN(115, out.lines, line_counter)
							data[pos] = t;
					} while (t != '\"');
					data[pos + 1] = '\0';
					int strlinelen = strlen(data);
					line_counter++;
					out.size++;
					if (!data)
						throw ERROR_THROW_IN(114, out.lines, line_counter)

						if (lexContainerLen == 0) {
							currentLex.line = out.lines;
							currentLex.col = line_counter;
						}
					currentLex.lexem = new unsigned char[strlinelen];
					for (int i = 0; i < strlinelen; i++)
						currentLex.lexem[i] = data[i];
					currentLex.lexem[strlinelen] = '\0';

					out.lexems.push_back(currentLex);

					if (lexContainerLen > MAX_LEXEM_LENGTH)
						throw ERROR_THROW_IN(113, out.lines, line_counter);
					break;
				}
				case IN::S://space
				{
					out.size++;
					line_counter++;
					if (lexContainerLen != 0) {
						lexContainer[lexContainerLen++] = '\0';
						currentLex.lexem = new unsigned char[lexContainerLen];
						for (int i = 0; i < lexContainerLen; i++)
							currentLex.lexem[i] = lexContainer[i];
						out.lexems.push_back(currentLex);
						delete[]lexContainer;
						lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
						lexContainerLen = 0;
					}
					break;
				}

				case IN::L:// одиночная лексема
				{
					out.size++;
					line_counter++;
					if (tmp == '-' && *(out.lexems.back().lexem) == '=')
					{
						if (lexContainerLen == 0) {
						currentLex.line = out.lines;
						currentLex.col = line_counter;
						}
						if (lexContainerLen >= MAX_LEXEM_LENGTH - 1)
							throw ERROR_THROW_IN(113, out.lines, line_counter);
						lexContainer[lexContainerLen++] = tmp;
					} 
					else if (tmp == '=' && *(out.lexems.back().lexem) == '=')
					{
						*(out.lexems.back().lexem) = '$';
					}
					else
					{
						
						if (lexContainerLen != 0) {

							lexContainer[lexContainerLen++] = '\0';
							currentLex.lexem = new unsigned char[lexContainerLen];
							for (int i = 0; i < lexContainerLen; i++)
								currentLex.lexem[i] = lexContainer[i];
							out.lexems.push_back(currentLex);
							delete[]lexContainer;
							lexContainerLen = 0;
						}
						lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
						lexContainer[0] = tmp;
						lexContainer[1] = '\0';
						lexContainerLen = 2;
						currentLex.line = out.lines;
						currentLex.col = line_counter;
						currentLex.lexem = new unsigned char[lexContainerLen];
						for (int i = 0; i < lexContainerLen; i++)
							currentLex.lexem[i] = lexContainer[i];
						out.lexems.push_back(currentLex);
						delete[]lexContainer;
						lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
						lexContainerLen = 0;
					}
					break;
				}
				case IN::F:
				{
					line_counter++;
					throw ERROR_THROW_IN(111, out.lines, line_counter)
						break;
				}
				case IN::I: 
				{
					do {
						line_counter++;
						out.ignor++;
						file >> tmp;
					} while (chars[(int)tmp] != IN::N);
				}
				case IN::N:
				{
					out.size++;
					out.lines++;
					line_counter = 0;
					if (lexContainerLen != 0) {
						lexContainer[lexContainerLen++] = '\0';
						currentLex.lexem = new unsigned char[lexContainerLen];
						for (int i = 0; i < lexContainerLen; i++)
							currentLex.lexem[i] = lexContainer[i];
						out.lexems.push_back(currentLex);
						delete[]lexContainer;
						lexContainerLen = 0;
						lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
					}
					break;
				}
				default:
				{
					break;
				}
				}
			}
			if (lexContainerLen != 0) {
				throw ERROR_THROW_IN(600, out.lines, line_counter);
			}
			delete[]lexContainer;
			file.close();

		}

		return out;
	}
}