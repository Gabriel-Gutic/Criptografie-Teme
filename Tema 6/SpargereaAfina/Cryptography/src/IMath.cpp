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
	while (y != Integer::Zero)
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

int IMath::Jacobi(const Integer& b, const Integer& p)
{
	Integer m = b;
	Integer n = p;
	int result = 1;

	{
		Integer power1 = 0;
		while (m != 0 && m % 2 == 0)
		{
			power1++;
			m /= 2;
		}

		if (power1 % 2 == 1)
		{
			Integer power2 = (n * n - 1) / 8;
			if (power2 % 2 == 1)
				result *= -1;
		}
	}

	while (true)
	{
		if (m == 1)
			return result;
		if (m == 0 || m == n)
		{
			return 0;
		}
		if (m < n)
		{
			Integer power = (m - 1) * (n - 1) / 4;
			if (power % 2 == 1)
			{
				result *= -1;
			}

			Integer temp = m;
			m = n;
			n = temp;
		}
		else
		{
			m = m % n;

			Integer power1 = 0;
			while (m != 0 && m % 2 == 0)
			{
				power1++;
				m /= 2;
			}

			if (power1 % 2 == 1)
			{
				Integer power2 = (n * n - 1) / 8;
				if (power2 % 2 == 1)
					result *= -1;
			}
		}
	}
}
