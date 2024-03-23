#include "pch.h"
#include "Integer.h"

#include "IMath.h"


Integer Integer::Zero = Integer(0);
Integer Integer::One = Integer(1);
Integer Integer::Nan = Integer::GetNan();


Integer::Integer(long long n)
	:m_Sign(0)
{
	m_Sign = n < 0;
	m_Digits.resize(IMath::DigitCount(n));
	
	int m = abs(n);
	int i = 0;
	while (m)
	{
		m_Digits[i++] = m % 10;
		m /= 10;
	}
}

Integer::Integer(std::string_view n)
	:m_Sign(0)
{
	int start = 0;
	if (n[0] == '-' || n[0] == '+')
	{
		m_Sign = n[0] == '-';
		start = 1;
	}

	m_Digits.resize(n.size() - start);
	for (int i = n.size() - 1; i >= start; i--)
	{
		m_Digits[n.size() - i - 1] = n[i] - '0';
	}
}

bool Integer::IsPositive() const
{
	return m_Sign == 0;
}

bool Integer::IsNegative() const
{
	return m_Sign == 1;
}

bool Integer::IsNan() const
{
	return m_Digits.size() == 0;
}

int Integer::DigitCount() const
{
	return m_Digits.size();
}

std::string Integer::ToString() const
{
	if (m_Digits.size() == 0)
		return "Nan";

	std::stringstream ss;
	if (m_Sign)
		ss << "-";
	for (int i = m_Digits.size() - 1; i >= 0; i--)
	{
		ss << (int)m_Digits[i];
	}
	return ss.str();
}

Integer Integer::Abs() const
{
	Integer result = *this;
	result.m_Sign = 0;
	return result;
}

Integer Integer::Sqrt() const
{
	if (IsNegative())
		return Integer::Nan;

	if (*this == 0)
		return 0;
	if (*this <= 3)
		return 1;

	Integer left = 2;
	Integer right = *this / 2;

	while (left < right)
	{
		Integer middle = (left + right) / 2;
		Integer product = middle * middle;
		if (product == *this)
		{
			return middle;
		}

		if (product > *this)
		{
			right = middle - 1;
		}
		else
		{
			left = middle + 1;
		}
	}
	
	if (left * left > *this)
		return left - 1;

	return left;
}

Integer Integer::MultiplyByPower10(int power) const
{
	if (*this == 0)
		return 0;

	Integer result;
	result.m_Sign = m_Sign;
	result.m_Digits.resize(m_Digits.size() + power);
	for (int i = 0; i < m_Digits.size(); i++)
	{
		result.m_Digits[i + power] = m_Digits[i];
	}

	return result;
}

Integer Integer::operator-() const
{
	Integer result = *this;
	result.m_Sign = !m_Sign;
	return result;
}

Integer& Integer::operator+=(const Integer& a)
{
	*this = *this + a;
	return *this;
}

Integer& Integer::operator-=(const Integer& a)
{
	*this = *this - a;
	return *this;
}

Integer& Integer::operator*=(const Integer& a)
{
	*this = *this * a;
	return *this;
}

Integer& Integer::operator/=(const Integer& a)
{
	*this = *this / a;
	return *this;
}

Integer& Integer::operator%=(const Integer& a)
{
	*this = *this % a;
	return *this;
}

Integer operator+(const Integer& a, const Integer& b)
{
	if (a.m_Digits.size() == 0 || b.m_Digits.size() == 0)
		return Integer::Nan;
	if (a.m_Digits.size() == 1 && a[0] == 0)
		return b;
	if (b.m_Digits.size() == 1 && b[0] == 0)
		return a;

	if (a.m_Sign != b.m_Sign)
	{
		if (a.IsPositive())
		{
			Integer temp = b;
			temp.m_Sign = 0;
			return a - temp;
		}
		else
		{
			Integer temp = a;
			temp.m_Sign = 0;
			return b - temp;
		}
	}

	Integer result;
	result.m_Digits.resize(std::max(a.m_Digits.size(), b.m_Digits.size()) + 1);
	result.m_Sign  = a.m_Sign;
	
	char r = 0;
	for (int i = 0; i < result.m_Digits.size() - 1; i++)
	{ 
		char c1 = i < a.m_Digits.size() ? a.m_Digits[i] : 0;
		char c2 = i < b.m_Digits.size() ? b.m_Digits[i] : 0;
	
		char newDigit = c1 + c2 + r;

		if (newDigit > 9)
		{
			result.m_Digits[i] = newDigit - 10;
			r = 1;
		}
		else
		{
			result.m_Digits[i] = newDigit;
			r = 0;
		}
	}

	if (r == 1)
	{
		result.m_Digits.back() = 1;
	}

	while (result.m_Digits.back() == 0 && result.m_Digits.size() > 1)
	{
		result.m_Digits.pop_back();
	}

	return result;
}

Integer operator-(const Integer& a, const Integer& b)
{
	if (a.IsNan() || b.IsNan())
		return Integer::Nan;
	if (a == b)
		return Integer::Zero;

	if (a.m_Sign != b.m_Sign)
	{
		return a + -b;
	}

	// Check witch number has the biggest absolute value
	Integer x = a;
	x.m_Sign = 0;
	Integer y = b;
	y.m_Sign = 0;

	bool aIsBigger = x > y;
	x = aIsBigger ? a : b;
	y = aIsBigger ? b : a;

	// Set the sign of the result;
	Integer result;
	if (aIsBigger)
	{
		result.m_Sign = x.m_Sign;
	}
	else
	{
		result.m_Sign = !x.m_Sign;
	}

	result.m_Digits.clear();

	int i;
	for (i = 0; i < y.m_Digits.size(); i++)
	{
		if (x.m_Digits[i] < y.m_Digits[i])
		{
			int j = i + 1;
			while (x.m_Digits[j] == 0)
			{
				j++;
			}

			x.m_Digits[j]--;
			if (x.m_Digits[j] == 0 && j == x.m_Digits.size() - 1)
				x.m_Digits.pop_back();
			for (int k = j - 1; k > i; k--)
				x.m_Digits[k] = 9;
			x.m_Digits[i] += 10;
		}

		result.m_Digits.push_back(x.m_Digits[i] - y.m_Digits[i]);
	}

	for (int j = i; j < x.m_Digits.size(); j++)
		result.m_Digits.push_back(x.m_Digits[j]);

	while (result.m_Digits.back() == 0)
		result.m_Digits.pop_back();

	return result;
}

Integer operator*(const Integer& a, const Integer& b)
{
	if (a.IsNan() || b.IsNan())
		return Integer::Nan;
	if (a.m_Digits.size() == 1 && a[0] == 0 || b.m_Digits.size() == 1 && b[0] == 0)
		return 0;
	if (a.m_Digits.size() == 1 && a[0] == 1)
	{
		if (a.IsPositive())
		{
			return b;
		}
		else
		{
			return -b;
		}
	}
	if (b.m_Digits.size() == 1 && b[0] == 1)
	{
		if (b.IsPositive())
		{
			return a;
		}
		else
		{
			return -a;
		}
	}

	Integer small, bigger;
	if (a.m_Digits.size() > b.m_Digits.size())
	{
		bigger = a;
		small = b;
	}
	else {
		bigger = b;
		small = a;
	}

	Integer result = 0;
	result.m_Sign = a.m_Sign != b.m_Sign;
	for (int i = 0; i < small.m_Digits.size(); i++)
	{
		for (int j = 0; j < bigger.m_Digits.size(); j++)
		{
			if (small.m_Digits[i] != 0 && bigger.m_Digits[j] != 0)
			{
				Integer product;
				char prod = small.m_Digits[i] * bigger.m_Digits[j];
				int k;
				for (k = 0; k < i + j; k++)
					product.m_Digits.push_back(0);
				product.m_Digits[k] = prod % 10;
				if (prod > 9)
					product.m_Digits.push_back(prod / 10);
				result += product;
			}
		}
	}
	return result;
}

std::pair<Integer, Integer> Integer::Euler(const Integer& a, const Integer& b)
{
	if (a.IsNan() || b.IsNan())
		return { Integer::Nan, Integer::Nan };
	if (b.m_Digits.size() == 1 && b[0] == 0)
		return { Integer::Nan, Integer::Nan };
	if (a.m_Digits.size() == 1 && a[0] == 0)
		return { 0, 0 };
	if (b.m_Digits.size() == 1 && b[0] == 1)
	{
		if (b.IsPositive())
		{
			return { a, 0 };
		}
		else
		{
			return { -a, 0 };
		}
	}

	Integer x = a.Abs();
	Integer y = b.Abs();

	if (x == y)
	{
		return { (a.m_Sign == b.m_Sign) ? 1 : -1 , 0 };
	}

	if (x < y)
	{
		if (a.IsPositive())
		{
			return { 0, a };
		}
		else
		{
			return { (b.IsPositive()) ? -1 : 1, y - x };
		}
	}

	Integer q, r; // x = y * q + r, 0 <= r < |y| 
	std::list<char> q_;

	Integer group;
	int next = x.m_Digits.size() - y.m_Digits.size() - 1;
	group.m_Digits.resize(y.m_Digits.size());
	for (int i = 0; i < group.m_Digits.size(); i++)
	{
		group.m_Digits[i] = x.m_Digits[i + x.m_Digits.size() - y.m_Digits.size()];
	}

	if (group < y)
	{
		group.m_Digits.insert(group.m_Digits.begin(), { x.m_Digits[next--] });
	}

	while (next >= -1)
	{
		char c;
		for (c = 0; c < 10; c++)
		{
			r = group - c * y;
			if (r < y)
				break;
		}
		if (c > 9)
		{
			return { Integer::Nan, Integer::Nan };
		}

		q_.push_front(c);
		group = r;
		if (group == 0)
			group.m_Digits.clear();
		if (next > -1)
		{
			group.m_Digits.insert(group.m_Digits.begin(), { x.m_Digits[next] });
		}
		next--;
	}
	q.m_Digits.resize(q_.size());
	int i = 0;
	for (char c : q_)
	{
		q.m_Digits[i++] = c;
	}

	q.m_Sign = a.m_Sign != b.m_Sign;

	if (a.IsPositive() || r == 0)
	{
		return { q, r };
	}

	if (b.IsPositive())
	{
		return { q - 1, y - r };
	}
	return { q + 1, y - r };
}

Integer operator/(const Integer& a, const Integer& b)
{
	return Integer::Euler(a, b).first;
}

Integer operator%(const Integer& a, const Integer& b)
{
	if (b.m_Digits.size() == 1 && b.m_Digits[0] == 2)
	{
		return a.m_Digits[0] % 2;
	}

	return Integer::Euler(a, b).second;
}

std::ostream& operator<<(std::ostream& os, const Integer& n)
{
	os << n.ToString();
	return os;
}

std::istream& operator>>(std::istream& is, Integer& n)
{
	std::string result;
	auto& succed = (is >> result);
	if (succed)
	{
		n = Integer(result);
	}
	return succed;
}

char Integer::operator[](int index) const
{
	int i = index;
	if (i < 0)
	{
		i = m_Digits.size() + i;
	}
	return m_Digits[i];
}

Integer Integer::GetNan()
{
	Integer result;
	result.m_Digits.clear();
	return result;
}

bool operator==(const Integer& a, const Integer& b)
{
	if (a.m_Digits.size() != b.m_Digits.size() || a.m_Sign != b.m_Sign)
		return false;

	for (int i = 0; i < a.m_Digits.size(); i++)
	{
		if (a[i] != b[i])
			return false;
	}

	return true;
}

bool operator!=(const Integer& a, const Integer& b)
{
	return !(a == b);
}

bool operator<=(const Integer& a, const Integer& b)
{
	if (a.IsNan() || b.IsNan())
		return false;
	if (a.IsNegative() && b.IsPositive())
		return true;
	if (a.IsPositive() && b.IsNegative())
		return false;
	if (a.m_Digits.size() > b.m_Digits.size())
		return a.IsNegative();
	if (a.m_Digits.size() < b.m_Digits.size())
		return a.IsPositive();

	for (int i = a.m_Digits.size() - 1; i >= 0; i--)
	{
		if (a[i] > b[i])
		{
			return a.IsNegative();
		}
		else if (a[i] < b[i])
		{
			return a.IsPositive();
		}
	}

	return true;
}

bool operator>=(const Integer& a, const Integer& b)
{
	if (a.IsNan() || b.IsNan())
		return false;
	if (a.IsNegative() && b.IsPositive())
		return false;
	if (a.IsPositive() && b.IsNegative())
		return true;
	if (a.m_Digits.size() > b.m_Digits.size())
		return a.IsPositive();
	if (a.m_Digits.size() < b.m_Digits.size())
		return a.IsNegative();

	for (int i = a.m_Digits.size() - 1; i >= 0; i--)
	{
		if (a[i] < b[i])
		{
			return a.IsNegative();
		}
		else if (a[i] > b[i])
		{
			return a.IsPositive();
		}
	}

	return true;
}

bool operator<(const Integer& a, const Integer& b)
{
	return !(a >= b);
}

bool operator>(const Integer& a, const Integer& b)
{
	return !(a <= b);
}
