#include "pch.h"
#include "Prime.h"

#include "IMath.h"


bool Prime::Divisions(const Integer& n)
{
	if (n == 0 || n == 1)
		return false;
	if (n == 2)
		return true;
	if (n % 2 == 0)
		return false;
	Integer s = n.Sqrt();
	for (int d = 3; d <= s; d++)
	{
		std::cout << d << std::endl;
		if (n % d == 0)
			return false;
	}
	return true;
}

bool Prime::Fermat(const Integer& n, int nr_incercari)
{
	if (n == 2)
		return true;
	if (n % 2 == 0)
		return false;
	for (; nr_incercari > 0; nr_incercari--)
	{
		Integer b = rand();
		b = 2 + b % (n - 2);
		if (IMath::Cmmdc(b, n) != 1)
			return false;
		if (Integer::Pow(b, n - 1, n) != 1)
			return false;
	}
	return true;
}

bool Prime::MillerRabin(const Integer& n, int nr_incercari)
{
	if (n == 2)
		return true;
	if (n % 2 == 0)
		return false;
	for (; nr_incercari > 0; nr_incercari--)
	{
		Integer s = 0, t = n - 1, b = rand();
		b = 2 + b % (n - 2);
		while (t % 2 == 0)
		{
			s++;
			t /= 2;
		}
		t = Integer::Pow(b, t, n);//in t pastram acum puterile b^t,b^(2t),...
		if (t != 1)
		{
			while ((t != n - 1) && (--s > 0))
			{
				t = (t * t) % n;
				if (t == 1)
					return false;
			}
			if (t != n - 1)
				return false;
		}
	}
	return true;
}
