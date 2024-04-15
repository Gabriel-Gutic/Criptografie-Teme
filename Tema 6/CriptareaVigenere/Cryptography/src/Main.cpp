#include "pch.h"

#include "Alphabet/Criptare.h"
#include "Matrix.h"


int main()
{
	Alphabet::ReadAlphabet("files/alfabet.txt");

	Matrix::N = Alphabet::GetCount();

	std::cout << "N = " << Alphabet::GetCount() << std::endl;

	int N = Alphabet::GetCount();

	Criptare::Vigenere("files/sursa.txt", "files/destinatie.txt", "HARRY");

	// std::cin.get();
	return 0;
}






