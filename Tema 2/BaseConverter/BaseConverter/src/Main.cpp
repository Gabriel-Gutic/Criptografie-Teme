#include "Number.h"

#include <iostream>


int main()
{
	std::string input;
	uint32_t base1 = 0;
	uint32_t base2 = 0;

	while (base1 < 2 || base1 > 26)
	{
		std::cout << "Introduceti baza 1 (intre 2 si 26): "; 
		std::cin >> base1;
	}

	while (base2 < 2 || base2 > 26)
	{
		std::cout << "Introduceti baza 2 (intre 2 si 26): ";
		std::cin >> base2;
	}

	std::cout << "Introduceti numarul ce trebuie convertit: ";
	std::cin >> input;

	Number number(base1, input);
	std::cout << "Numarul introdus, in baza " << base1 << ": " << number << std::endl;

	unsigned long long base10Number = number.ToInteger();

	std::cout << "Numarul introdus, in baza 10: " << base10Number << std::endl;

	Number result(base2, base10Number);

	std::cout << "Numarul introdus, in baza " << base2 << ": " << result << std::endl;

	return 0;
}