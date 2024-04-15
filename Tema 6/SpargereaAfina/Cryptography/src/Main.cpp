#include "pch.h"

#include "Alphabet/Criptare.h"
#include "Matrix.h"


int main()
{
	Alphabet::ReadAlphabet("files/alfabet.txt");

	Matrix::N = Alphabet::GetCount();

	std::cout << "N = " << Alphabet::GetCount() << std::endl;

	int N = Alphabet::GetCount();

	
	Matrix A(2, 2), B(2, 1);
	A[0][0] = 2;
	A[0][1] = 3;
	A[1][0] = 7;
	A[1][1] = 8;

	B[0][0] = 2;
	B[1][0] = 3;

	Criptare::Afina("files/sursa1.txt", "files/sursa.txt", A, B);
	
	
	Spargere::Afina("files/sursa.txt", "files/destinatie.txt", "a ", " c", "i ", " s");
	

	// std::cin.get();
	return 0;
}






