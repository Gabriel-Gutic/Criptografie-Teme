#include "pch.h"
#include "AKS.h"

#include "Polynomial.h"


bool prim(int n)
{
	if (n == 0 || n == 1)
		return false;
	if (n == 2)
		return true;
	if (n % 2 == 0)
		return false;
	for (int d = 3; d <= sqrt(n); d+=2)
	{
		if (n % d == 0)
			return false;
	}
	return true;
}


int main()
{
	std::ofstream output("files/numbers.txt");
	for (int i = 0; i < 500; i++)
	{
		output << i << " " << prim(i) << std::endl;
	}
	output.close();

	if (1)
	{
		std::ifstream input("files/numbers.txt");
		int n;
		bool prim;

		bool passed = true;
		while (input >> n >> prim && passed)
		{
			bool aks = AKS(n);
			if (aks && !prim)
			{
				passed = false;
				std::cout << "Pentru " << n << " ar trebui sa rezulte ca NU e prim" << std::endl;
			}
			else if (!aks && prim)
			{
				passed = false;
				std::cout << "Pentru " << n << " ar trebui sa rezulte ca e prim" << std::endl;
			}
		}

		if (passed)
		{
			std::cout << "Algoritmul a trecut toate testele!" << std::endl;
		}
	}

	std::cout << "-------------------------------------" << std::endl;

	int n = 31;
	// int n = 7417;
	if (AKS(n))
	{
		std::cout << n << " e prim" << std::endl;
	}
	else
	{
		std::cout << n << " NU e prim" << std::endl;
	}

	return 0;
}