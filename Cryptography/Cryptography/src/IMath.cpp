#include "pch.h"
#include "IMath.h"

int IMath::DigitCount(long long n)
{
    return n == 0 ? 1 : ((int)log10(abs(n)) + 1);
}

int IMath::BitCount(long long n)
{
    return n == 0 ? 1 : ((int)log2(abs(n)) + 1);
}

Integer IMath::Cmmdc(const Integer& a, const Integer& b)
{
	Integer x = a.Abs();
	Integer y = b.Abs();

	Integer r;
	while (y != 0)
	{
		r = x % y;
		x = y;
		y = r;
	}
	return x;

	//while (x != y)
	//{
	//	if (x > y)
	//		x -= y;
	//	else
	//		y -= x;
	//}
	//return x;
}
