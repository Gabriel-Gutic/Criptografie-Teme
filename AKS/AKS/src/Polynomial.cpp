#include "pch.h"
#include "Polynomial.h"


Polynomial::Polynomial(const std::initializer_list<Coefficient>& list)
{
	m_Coefficients = list;
}

Polynomial::Polynomial(const Coefficient& coef, int power)
{
	m_Coefficients.resize(power + 1);
	m_Coefficients[m_Coefficients.size() - 1] = coef;
}

int Polynomial::GetDegree() const
{
	return m_Coefficients.size() - 1;
}

int Polynomial::GetCount() const
{
	return m_Coefficients.size();
}

const std::vector<Coefficient>& Polynomial::GetCoefficients() const
{
	return m_Coefficients;
}

std::vector<Coefficient>& Polynomial::GetCoefficients()
{
	return m_Coefficients;
}

Polynomial Polynomial::Remainder(int power) const
{
	Polynomial result = *this;

	int n = GetDegree();
	for (int k = n; k >= power; k--)
	{
		result.m_Coefficients[k - power] = result.m_Coefficients[k - power] + result.m_Coefficients[k];
	}

	result.m_Coefficients.resize(power);

	while (result.m_Coefficients.back() == 0 && result.m_Coefficients.size() > 1)
	{
		result.m_Coefficients.pop_back();
	}

	return result;
}

Polynomial Polynomial::NewtonCoefficients(int power)
{
	Integer** coefficients;
	coefficients = new Integer*[power + 2];

	for (int i = 0; i < power + 2; i++)
	{
		coefficients[i] = new Integer[i + 1];
	}

	for (int n = 0; n < power + 2; n++)
	{
		coefficients[n][0] = 1;
		coefficients[n][n] = 1;
	}

	// O(2) algorithm
	for (int n = 2; n < power + 2; n++)
	{
		for (int k = 1; k < n; k++)
		{
			coefficients[n][k] = modulo(coefficients[n - 1][k - 1] + coefficients[n - 1][k], power);
		}
	}

	Polynomial P;
	P.m_Coefficients.resize(power + 1);
	for (int i = 0; i <= power; i++)
	{
		P.m_Coefficients[i] = Coefficient(coefficients[power][power - i], power - i);
	}

	return P;
}

Polynomial operator%(const Polynomial& P, int n)
{
	Polynomial result;
	result.m_Coefficients.resize(P.m_Coefficients.size());

	for (int i = 0; i < P.m_Coefficients.size(); i++)
	{
		result.m_Coefficients[i] = P.m_Coefficients[i] % n;
	}

	while (result.m_Coefficients.back() == 0 && result.m_Coefficients.size() > 1)
	{
		result.m_Coefficients.pop_back();
	}

	return result;
}

Polynomial operator-(const Polynomial& P1, const Polynomial& P2)
{
	Polynomial result;
	result.m_Coefficients.resize(std::max(P1.m_Coefficients.size(), P2.m_Coefficients.size()));
	for (int i = 0; i < result.m_Coefficients.size(); i++)
	{
		Coefficient x = i < P1.m_Coefficients.size() ? P1.m_Coefficients[i] : Coefficient({0});
		Coefficient y = i < P2.m_Coefficients.size() ? P2.m_Coefficients[i] : Coefficient({ 0 });

		result.m_Coefficients[i] = x - y;
	}

	while (result.m_Coefficients.back() == 0 && result.m_Coefficients.size() > 1)
	{
		result.m_Coefficients.pop_back();
	}

	return result;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& P)
{
	for (int i = P.GetDegree(); i >= 0; i--)
	{
		os << "(" << P.m_Coefficients[i] << ")";
		if (i != 0)
		{
			os << " * x^(" << i << ") + ";
		}
	}

	return os;
}
