#include "pch.h"
#include "Writer.h"
#include "Int2.h"


long long modulo(long long a, long long b)
{
	if (a < 0)
	{
		if (b >= 0)
		{
			a = b - (-a) % b;
		}
		else
		{
			return (-b * (a / b + 1)) + a;
		}
	}
	if (a >= b)
	{
		return a % b;
	}
	return a;
}


long long divide(long long a, long long b)
{
	return (a - modulo(a, b)) / b;
}


std::string NeedParentheses(long long a)
{
	if (a >= 0)
	{
		return std::to_string(a);
	}
	return "(" + std::to_string(a) + ")";
}


void gcd(long long a, long long b, std::string_view writerPath)
{
	Writer writer(writerPath);

	writer << "\\noindent \n";
	writer << "\\( \n";
	writer << "\\cmmdc(" << a << ", " << b << ") = ? \\\\ \n";
	writer << "x_{" << a << "} = (1, 0) \n \\\\ \n";
	writer << "x_{" << b << "} = (0, 1) \n";
	writer << "\\) \n \\\\ \n";

	long long first = a, second = b;
	Int2 x1(1, 0), x2(0, 1);

	while (second != 0)
	{
		long long remainder = modulo(first, second);
		long long quotient = divide(first, second);

		if (remainder == 0)
			break;

		Int2 temp = x2;
		x2 = x1 - quotient * x2;
		x1 = temp;

		writer << "\\begin{paracol}{2}\n";
		writer << "\\( \n";
		writer << first << " = " << second << " \\cdot " <<  NeedParentheses(quotient) << " + " << remainder << "\n";
		writer << "\\) \n";

		writer << "\\switchcolumn\n";

		writer << "\\( \n";
		writer << "\\Rightarrow x_{" << remainder << "} = x_{" << first << "} " << (quotient < 0 ? "+" : "-") << abs(quotient) << " \\cdot x_{" << second << "} = " << x2 << "\n";
		writer << "\\) \n";

		writer << "\\end{paracol} \n";

		first = second;
		second = remainder;
	}

	writer << "\\[ \n";
	writer << second << " = " << a << " \\cdot \\underline{" << NeedParentheses(x2.GetX()) << "} + " << NeedParentheses(b) << " \\cdot \\underline{" << NeedParentheses(x2.GetY()) << "} \n";
	writer << "\\] \n";
}


void inverse(long long n, long long a, std::string_view writerPath)
{
	Writer writer(writerPath);

	writer << "C\\u aut\\u am inversul lui \\(" << a << "\\) \\^ in \\( \\mathbb{Z}_{" << n << "}\\) \\\\ \n";
	
	writer << "\\noindent \n";
	writer << "\\( \n";
	writer << "\\cmmdc(" << n << ", " << a << ") = ? \\\\ \n";
	writer << "x_{" << n << "} = (1, 0) \n \\\\ \n";
	writer << "x_{" << a << "} = (0, 1) \n";
	writer << "\\) \n \\\\ \n";

	long long first = n, second = a;
	Int2 x1(1, 0), x2(0, 1);

	while (second != 0)
	{
		long long remainder = modulo(first, second);
		long long quotient = divide(first, second);

		if (remainder == 0)
			break;

		Int2 temp = x2;
		x2 = x1 - quotient * x2;
		x1 = temp;

		writer << "\\begin{paracol}{2}\n";
		writer << "\\( \n";
		writer << first << " = " << second << " \\cdot " << NeedParentheses(quotient) << " + " << remainder << "\n";
		writer << "\\) \n";

		writer << "\\switchcolumn\n";

		writer << "\\( \n";
		writer << "\\Rightarrow x_{" << remainder << "} = x_{" << first << "} " << (quotient < 0 ? "+" : "-") << abs(quotient) << " \\cdot x_{" << second << "} = " << x2 << "\n";
		writer << "\\) \n";

		writer << "\\end{paracol} \n";

		first = second;
		second = remainder;
	}

	if (second != 1)
	{
		writer << "\\[ \n";
		writer << "\\cmmdc(" << n << ", " << a << ") = " << second << " \\neq 1 \\Rightarrow " << a << "\\text{ nu e inversabil \\^in } \\mathbb{Z}_{" << n << "} \n";
		writer << "\\] \n";
	}
	else
	{
		writer << "\\[ \n";
		writer << "1 = " << n << " \\cdot \\underline{" << NeedParentheses(x2.GetX()) << "} + " << NeedParentheses(a) << " \\cdot \\underline{" << NeedParentheses(x2.GetY()) << "} \n";
		writer << "\\] \n";

		writer << "\\[ \n";
		writer << "1 \\equiv " << a << " \\cdot " << NeedParentheses(x2.GetY()) << " \\mod(" << n << ") \n";
		writer << "\\] \n";

		writer << "\\[ \n";
		writer << "{" << a << "}^{-1} \\equiv " << x2.GetY() << " \\mod(" << n << ") \n";
		writer << "\\] \n";

		long long result = modulo(x2.GetY(), n);

		writer << "\\[ \n";
		writer << "{" << a << "}^{-1} \\equiv " << result << " \\mod(" << n << ") \n";
		writer << "\\] \n";

		writer << "\\[ \n";
		writer << "{" << a << "}^{-1} = " << result << " \\text{ \\^in } \\mathbb{Z}_{" << n << "} \n";
		writer << "\\] \n";
	}
}


int main()
{
	int choice = -1;

	do
	{
		std::cout << "Ce doriti sa calculati?" << std::endl;
		std::cout << "Introduceti 1 pentru CEL MAI MARE DIVIZOR COMUN" << std::endl;
		std::cout << "Introduceti 2 pentru INVERSUL UNUI ELEMENT DIN Zn" << std::endl;
		std::cout << "Introduceti 0 pentru a iesi" << std::endl << std::endl;
		std::cout << "Introduceti comanda: "; std::cin >> choice;

		switch (choice)
		{
		case 1:
			{
				long long a, b;
				std::string filename;
				std::cout << "Introduceti cele 2 numere a si b" << std::endl;
				std::cout << "a = "; std::cin >> a;
				while (a == 0)
				{
					std::cout << "a nu poate fi 0!\n";
					std::cout << "a = "; std::cin >> a;
				}
				std::cout << "b = "; std::cin >> b;
				while (b == 0)
				{
					std::cout << "b nu poate fi 0!\n";
					std::cout << "b = "; std::cin >> b;
				}
				std::cout << "Introduceti numele fisierului (fara spatii): ";
				std::cin >> filename;
				gcd(a, b, filename);
			}
			break;
		case 2:
			{
				long long n;
				std::cout << "Introduceti o valoare pentru n\n";
				std::cout << "n = "; std::cin >> n;

				while (n < 2)
				{
					std::cout << "n trebuie sa fie mai mare decat 1!\n";
					std::cout << "n = "; std::cin >> n;
				}

				long long a;
				std::cout << "Introduceti o valoare pentru a\n";
				std::cout << "a = "; std::cin >> a;

				std::string filename;
				std::cout << "Introduceti numele fisierului (fara spatii): ";
				std::cin >> filename;

				inverse(n, a, filename);
			}
			break;
		}

		system("CLS");
	} while (choice != 0);
}