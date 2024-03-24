#include "pch.h"
#include "IntegerDivisionTest.h"

#include "Integer.h"


void IntegerDivisionTest::Run()
{
	std::ifstream input("tests/Division.txt");

	Integer a, b, q, r;
	while (input >> a >> b >> q >> r)
	{
		Integer q1 = a / b;
		Integer r1 = a % b;

		if (q1 != q || r1 != r)
		{
			Assert("Division Test failed for numbers: " + a.ToString() + " and " + b.ToString());
		}
	}
	
	std::cout << "All tests passed!" << std::endl;

	input.close();
}
