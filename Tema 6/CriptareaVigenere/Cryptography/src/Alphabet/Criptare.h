#pragma once
#include "Alphabet.h"
#include "Matrix.h"


struct Block
{
	char* Chars;
	int Length;
	int Count;

	Block(int length = 1);
	Block(const char* chars);
	Block(const Block& other);
	Block& operator=(const Block& other);
	~Block();

	bool OnlyLetters() const;

	Matrix ToMatrix() const;
	char& operator[](int index);
	const char& operator[](int index) const;
	friend bool operator==(const Block& b1, const Block& b2);
};


class Criptare
{
public:
	static void Afina(const char* in, const char* out, const Matrix& A, const Matrix& B);
	static void Vigenere(const char* in, const char* out, const char* key);
};

class Spargere
{
public:
	static void Afina(const char* in, const char* out, const char frecvent0[2], const char frecvent1[2], const char frecvent2[2], const char frecvent3[2]);
private:
	static void CitireFrecvente(const char* in, int lungime = 1);
	static void OrdonareFrecvente();
private:
	static std::vector<Block> s_Blocks;
};