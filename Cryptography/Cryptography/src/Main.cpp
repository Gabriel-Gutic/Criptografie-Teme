#include "pch.h"
#include "Integer.h"

#include "Tests/SqrtTest.h"
#include "IMath.h"
#include "Prime.h"


int main()
{
	// Simbolul lui Jacobi
	Integer a = 58, b = 71;

	std::cout << "Jacobi(" << a << ", " << b << ") = " << IMath::Jacobi(a, b) << "\n\n\n";

	// Solovay Strassen
	Integer n = Integer("222334565193649");
	int nrIncercari = 10;

	std::cout << "Algoritmul Solovay Strassen pentru n = " << n << " cu " << nrIncercari << " incercari\n\n";

	bool prime = Prime::SolovayStrassen(n, nrIncercari);
	if (prime)
	{
		std::cout << "n = " << n << " poate fi prim\n";
	}
	else
	{
		std::cout << "n = " << n << " NU e prim\n";
	}

	std::cin.get();
	return 0;
}