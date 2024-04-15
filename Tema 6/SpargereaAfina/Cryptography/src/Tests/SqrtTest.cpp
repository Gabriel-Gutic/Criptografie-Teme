#include "pch.h"
#include "SqrtTest.h"

#include "Integer.h"


void SqrtTest::Run()
{
	for (int i = 0; i < 1000; i++)
	{
		Integer n = i;
		Integer sq = n.Sqrt();
		if (sq != (int)sqrt(i))
		{
			Assert("Sqrt Test failed for integer: " + n.ToString() + ", Sqrt:" + sq.ToString());
		}
	}

	std::cout << "All tests passed!" << std::endl;
}
