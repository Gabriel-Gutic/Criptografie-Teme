#pragma once


class Alphabet
{
private:
	Alphabet();
public:
	static void ReadAlphabet(const char* filepath);

	static char ToChar(int code);
	static int ToCode(char chr);

	static int GetCount();
private:
	static char s_Chars[100];
	static int s_Count;
};