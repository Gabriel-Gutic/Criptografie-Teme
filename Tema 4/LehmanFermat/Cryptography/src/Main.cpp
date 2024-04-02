#include "pch.h"
#include "Integer.h"

#include "IMath.h"
#include "Prime.h"


int main()
{
	Integer n = 12103;
	std::cout << "Metoda lui Euclid pentru n = " << n << std::endl;

	Integer* result = IMath::LehmanFermat(n);
	if (result)
	{
		std::cout << "p = " << result[0] << std::endl;
		std::cout << "q = " << result[1] << std::endl;

	}
	else
	{
		std::cout << "Algoritmul a esuat!" << std::endl;
	}

	std::cin.get();
	return 0;
}