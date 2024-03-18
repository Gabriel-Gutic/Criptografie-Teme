#include "pch.h"
#include "Coefficient.h"


Coefficient::Coefficient(const std::initializer_list<Integer>& list)
{
	m_Terms = list;
}

Coefficient::Coefficient(const Integer& term, int power)
{
	m_Terms.resize(power + 1);
	m_Terms[m_Terms.size() - 1] = term;
}

int Coefficient::GetDegree() const
{
	return m_Terms.size() - 1;
}

int Coefficient::GetCount() const
{
	return m_Terms.size();
}

const std::vector<Integer>& Coefficient::GetTerms() const
{
	return m_Terms;
}

Integer Coefficient::Evaluate(Integer a, Integer n) const
{
	std::vector<Integer> powers; // values of a^i
	powers.resize(m_Terms.size());

	powers[0] = 1;
	for (int i = 1; i < m_Terms.size(); i++)
	{
		powers[i] = modulo(powers[i - 1] * a, n);
	}

	Integer result = 0;

	for (int i = 0; i < m_Terms.size(); i++)
	{
		if (m_Terms[i] == 0)
		{
			continue;
		}

		result += modulo(m_Terms[i] * powers[i], n);
	}

	return result;
}

Coefficient Coefficient::operator-() const
{
	Coefficient result;
	result.m_Terms.resize(m_Terms.size());

	for (int i = 0; i < m_Terms.size(); i++)
	{
		result.m_Terms[i] = -m_Terms[i];
	}

	return result;
}

Coefficient operator+(const Coefficient& c1, const Coefficient& c2)
{
	Coefficient result;
	result.m_Terms.resize(std::max(c1.m_Terms.size(), c2.m_Terms.size()));
	for (int i = 0; i < result.m_Terms.size(); i++)
	{
		Integer x = i < c1.m_Terms.size() ? c1.m_Terms[i] : 0;
		Integer y = i < c2.m_Terms.size() ? c2.m_Terms[i] : 0;

		result.m_Terms[i] = x + y;
	}

	while (result.m_Terms.back() == 0 && result.m_Terms.size() > 1)
	{
		result.m_Terms.pop_back();
	}

	return result;
}

Coefficient operator-(const Coefficient& c1, const Coefficient& c2)
{
	return c1 + -c2;
}

Coefficient operator*(const Coefficient& c1, const Coefficient& c2)
{
	Coefficient result;
	int size = c1.GetDegree() + c2.GetDegree() + 1;
	result.m_Terms.resize(size);

	for (int i = 0; i < size; i++)
	{
		Integer sum = 0;
		for (int j = 0; j <= i; j++)
			if (j < c1.m_Terms.size() && (i - j) < c2.m_Terms.size())
			{
				sum += c1.m_Terms[j] * c2.m_Terms[i - j];
			}
		result.m_Terms[i] = sum;
	}

	return result;
}

Coefficient operator%(const Coefficient& c, int n)
{
	Coefficient result;
	result.m_Terms.resize(c.m_Terms.size());

	for (int i = 0; i < result.GetCount(); i++)
	{
		result.m_Terms[i] = modulo(c.m_Terms[i], n);
	}

	while (result.m_Terms.back() == 0 && result.m_Terms.size() > 1)
	{
		result.m_Terms.pop_back();
	}

	return result;
}

bool operator==(const Coefficient& c, const Integer& n)
{
	return c.GetDegree() == 0 && c.m_Terms[0] == 0;
}

std::ostream& operator<<(std::ostream& os, const Coefficient& c)
{
	bool isZero = true;
	for (int i = c.GetDegree(); i >= 0; i--)
	{
		if (c.m_Terms[i] != 0)
		{
			isZero = false;
			if (i != c.GetDegree())
				os << " + ";
			os << c.m_Terms[i];
			if (i != 0)
			{
				os << " * a^(" << i << ")";
			}
		}
	}

	if (isZero)
		os << 0;

	return os;
}
