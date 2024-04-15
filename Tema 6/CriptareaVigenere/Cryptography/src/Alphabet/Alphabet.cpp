#include "pch.h"
#include "Alphabet.h"

#include "Laborator.h"


int Alphabet::s_Count = 0;
char Alphabet::s_Chars[];

void Alphabet::ReadAlphabet(const char* filepath)
{
	std::ifstream input(filepath);

	if (!input.good())
		throw std::exception("File not found!");

	char c;
	while (input >> std::noskipws >> c)
	{
		s_Chars[s_Count++] = c;
	}
	if (s_Count == 0)
		throw std::exception("Alfabetul dat are 0 caractere");
	input.close();
}

char Alphabet::ToChar(int code)
{
	return s_Chars[modulo(code, s_Count)];
}

int Alphabet::ToCode(char chr)
{
	for (int i = 0; i < s_Count; i++)
		if (s_Chars[i] == chr)
			return i;
	std::cout << chr << std::endl;
	throw std::exception("Invalid char!");
}

int Alphabet::GetCount()
{
	return s_Count;
}
