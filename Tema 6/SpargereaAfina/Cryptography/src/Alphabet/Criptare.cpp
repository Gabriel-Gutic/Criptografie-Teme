#include "pch.h"
#include "Criptare.h"

#include "Laborator.h"


std::vector<Block> Spargere::s_Blocks;

void Spargere::Afina(const char* in, const char* out, const char frecvent0[2], const char frecvent1[2], const char frecvent2[2], const char frecvent3[2])
{
	CitireFrecvente(in, 2);
	OrdonareFrecvente();
	
	for (int i = 0; i < 4; i++)
	{
		std::cout << s_Blocks[i].Chars << std::endl;
	}

	int N = Alphabet::GetCount();
	int b0 = modulo(Alphabet::ToCode(s_Blocks[0][0]) - Alphabet::ToCode(s_Blocks[1][0]), N);
	int b1 = modulo(Alphabet::ToCode(s_Blocks[0][1]) - Alphabet::ToCode(s_Blocks[1][1]), N);
	int b2 = modulo(Alphabet::ToCode(s_Blocks[2][0]) - Alphabet::ToCode(s_Blocks[3][0]), N);
	int b3 = modulo(Alphabet::ToCode(s_Blocks[2][1]) - Alphabet::ToCode(s_Blocks[3][1]), N);

	int f0 = modulo(Alphabet::ToCode(frecvent0[0]) - Alphabet::ToCode(frecvent1[0]), N);
	int f1 = modulo(Alphabet::ToCode(frecvent0[1]) - Alphabet::ToCode(frecvent1[1]), N);
	int f2 = modulo(Alphabet::ToCode(frecvent2[0]) - Alphabet::ToCode(frecvent3[0]), N);
	int f3 = modulo(Alphabet::ToCode(frecvent2[1]) - Alphabet::ToCode(frecvent3[1]), N);

	int a, b, c, d;
	int invers1 = invers(b1, N);
	int invers2 = invers(b3, N);
	int invers3 = invers(b0 * b3 - b2 * b1, N);

	if (invers3 == -1)
	{
		std::cout << "Nu s-au putut determina inversele!" << std::endl;
		return;
	}

	a = modulo((f0 * b3 - f2 * b1) * invers3, N);
	c = modulo((f1 * b3 - f3 * b1) * invers3, N);

	if (b1 != 0)
	{
		b = modulo((f0 - a * b0) * invers1, N);
		d = modulo((f1 - c * b0) * invers1, N);
	}
	else
	{
		b = modulo((f2 - a * b2) * invers2, N);
		d = modulo((f3 - c * b2) * invers2, N);
	}

	Matrix A(2, 2);
	A[0][0] = a;
	A[0][1] = b;
	A[1][0] = c;
	A[1][1] = d;

	Matrix F0(2, 1);
	F0[0][0] = Alphabet::ToCode(frecvent0[0]);
	F0[1][0] = Alphabet::ToCode(frecvent0[1]);
	Matrix B0(2, 1);
	B0[0][0] = Alphabet::ToCode(s_Blocks[0][0]);
	B0[1][0] = Alphabet::ToCode(s_Blocks[0][1]);
	Matrix B = F0 - A * B0;

	std::ifstream input(in);
	std::ofstream output(out);

	char c1, c2;
	while (input >> std::noskipws >> c1)
	{
		if (!(input >> std::noskipws >> c2))
		{
			c2 = 0;
		}

		Matrix x(2, 1);
		x[0][0] = Alphabet::ToCode(c1);
		x[1][0] = Alphabet::ToCode(c2);

		Matrix result = A * x + B;

		output << Alphabet::ToChar(result[0][0]) << Alphabet::ToChar(result[1][0]);
	}

	input.close();
	output.close();
}

void Spargere::CitireFrecvente(const char* in, int lungime)
{
	std::ifstream input(in);

	char c;
	Block block(lungime);

	while (true)
	{
		for (int i = 0; i < lungime; i++)
		{
			if (!(input >> std::noskipws >> c))
			{
				input.close();
				return;
			}

			block[i] = c;
		}

		bool found = false;
		for (Block& b : s_Blocks)
		{
			if (b == block)
			{
				b.Count++;
				found = true;
			}
		}
		if (!found)
			s_Blocks.push_back(block);
	}
}

void Spargere::OrdonareFrecvente()
{
	std::sort(s_Blocks.begin(), s_Blocks.end(), [](const Block& b1, const Block& b2)
		{
			return b1.Count > b2.Count;
		});
}

bool operator==(const Block& b1, const Block& b2)
{
	return !strcmp(b1.Chars, b2.Chars);
}

Block::Block(int length)
	:Count(1)
{
	Length = length;
	Chars = new char[Length + 1];
	for (int i = 0; i < Length; i++)
	{
		Chars[i] = ' ';
	}
	Chars[Length] = 0;
}

Block::Block(const char* chars)
	:Count(1)
{
	Length = strlen(chars);
	Chars = new char[Length + 1];
	for (int i = 0; i < Length; i++)
	{
		Chars[i] = chars[i];
	}
	Chars[Length] = 0;
}

Block::Block(const Block& other)
{
	Count = other.Count;
	Length = other.Length;
	Chars = new char[Length + 1];
	for (int i = 0; i < Length; i++)
	{
		Chars[i] = other.Chars[i];
	}
	Chars[Length] = 0;
}

Block& Block::operator=(const Block& other)
{
	if (this != &other)
	{
		Length = other.Length;
		Count = other.Count;

		delete[] Chars;
		Chars = new char[Length + 1];
		for (int i = 0; i < Length; i++)
		{
			Chars[i] = other.Chars[i];
		}
		Chars[Length] = 0;
	}
	return *this;
}

Block::~Block()
{
	delete[] Chars;
}

bool Block::OnlyLetters() const
{
	for (int i = 0; i < Length; i++)
		if (!('a' <= Chars[i] && Chars[i] <= 'z'))
			return false;
	return true;
}

Matrix Block::ToMatrix() const
{
	Matrix M(Length, 1);

	for (int i = 0; i < Length; i++)
	{
		M[i][0] = Alphabet::ToCode(Chars[i]);
	}

	return M;
}

char& Block::operator[](int index)
{
	return Chars[index];
}

const char& Block::operator[](int index) const
{
	return Chars[index];
}

void Criptare::Afina(const char* in, const char* out, const Matrix& A, const Matrix& B)
{
	std::ifstream input(in);
	std::ofstream output(out);

	char c1, c2;
	while (input >> std::noskipws >> c1 >> std::noskipws >> c2)
	{
		Matrix x(2, 1);
		x[0][0] = Alphabet::ToCode(c1);
		x[1][0] = Alphabet::ToCode(c2);

		Matrix result = A * x + B;
		output << Alphabet::ToChar(result[0][0]) << Alphabet::ToChar(result[1][0]);
	}

	input.close();
	output.close();
}
