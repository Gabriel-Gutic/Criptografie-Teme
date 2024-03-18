#pragma once

#include "Polynomial.h"


int EulerPhi(int r)
{
	int result = r;

	int d = 2;
	while (r != 1)
	{
		if (r % d == 0)
		{
			r /= d;

			result /= d;
			result *= (d - 1);

			while (r % d == 0)
			{
				r /= d;
			}
		}
		d++;
	}

	return result;
}


bool IsNullPolynomial(const Polynomial& P, Integer a, Integer n)
{
	for (int i = 0; i < P.GetCoefficients().size(); i++)
	{
		Integer term = modulo(P.GetCoefficients()[i].Evaluate(a, n), n);
		if (term != 0)
			return false;
	}
	return true;
}


bool AKS(int n)
{
	if (n == 0 || n == 1)
		return false;

	double log2n = log2(n);
	int ilog2n = (int)log2n;

	// Step 1
	// Check if there is a in N and b > 1 such that n = a^b
	for (int b = 2; b <= ilog2n; b++) // O(k^4)
	{
		double a = pow(n, 1.0 / b);
		if ((int)a == a)
		{
			return false;
		}
	}

	// Step 2
	// Find r natural, such  o_r(n) > 4*log^2(n), r < 16 * log^5(n)
	// We can skip r if r and n are not coprime
	// When n > 300_000_000 => n << 16 * log^5(n)
	int maxOrd = (int)(log2n * log2n);
	int maxr = std::min(n + 1, (int)(16 * log2n * log2n * log2n * log2n * log2n));
	int r;
	bool notFound = true;
	for (r = 2; r < maxr && notFound; r++)
	{
		notFound = false;
		for (int k = 1; k <= maxOrd && (!notFound); k++)
		{
			int temp = a_la_b_mod_c(n, k, r);
			notFound = (temp == 1 || temp == 0);
		}
	}
	r--;

	// Step 3
	for (int a = r; a > 1; a--)
	{
		int c = cmmdc(a, n); // O(k^3)
		if (c > 1 && c < n)
			return false;
	}

	// Step 4
	if (n <= r)
	{
		return true;
	}
	
	// Step 5
	Polynomial P1 = Polynomial::NewtonCoefficients(n);
	P1 = P1.Remainder(r);
	P1 = P1 % n;

	Polynomial P2(Coefficient({ 1 }), n);
	P2.GetCoefficients()[0] = Coefficient({ 0, 1 });
	P2 = P2.Remainder(r);

	Polynomial P = P1 - P2;
	// std::cout << P << std::endl;

	Integer maxim = floor(sqrt(EulerPhi(r)) * log2n);
	for (int a = 1; a <= maxim; a++)
	{
		if (!IsNullPolynomial(P, a, n))
		{
			return false;
		}
	}
	
	// Step 6
	return true;
}