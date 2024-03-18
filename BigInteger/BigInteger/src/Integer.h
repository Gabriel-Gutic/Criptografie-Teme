#pragma once
#include <iostream>
#include <string>
#include <sstream>


class Integer
{
public:
	Integer(long long value = 0);
	Integer(const std::string& value);

	std::string ToString() const;

	friend std::ostream& operator<<(std::ostream& os, const Integer& k);
private:
	// 0 = '+', 1 = '-'
	bool m_Sign; 
	int m_Count;
	uint8_t* m_Digits;
};

Integer::Integer(long long value)
	:m_Sign(0), m_Count(0), m_Digits(nullptr)
{
	m_Sign = value >= 0 ? 0 : 1;
	m_Count = value == 0 ? 1 : (int)(log10(abs(value))) + 1;

	m_Digits = new uint8_t[m_Count];

	long long temp = abs(value);

	for (int i = 0; i < m_Count; i++)
	{
		m_Digits[i] = temp % 10;
		temp /= 10;
	}
}

Integer::Integer(const std::string& value)
	:m_Sign(0), m_Count(0), m_Digits(nullptr)
{
	int start = 0;
	m_Count = value.size();
	if (value[0] == '-' || value[0] == '+')
	{
		m_Sign = value[0] == '-' ? 1 : 0;
		m_Count--;
		start = 1;
	}

	m_Digits = new uint8_t[m_Count];

	for (int i = start; i < value.size(); i++)
	{
		if (!isdigit(value[i]))
		{
			std::cout << "ERROR: Invalid digit in Integer: '" << value[i] - '0' << "'" << std::endl;
			__debugbreak();
		}

		m_Digits[m_Count - i + start - 1] = value[i] - '0';
	}

	if (m_Count == 1 && m_Digits[0] == 0)
	{
		m_Sign = 0;
	}
}

std::string Integer::ToString() const
{
	std::stringstream ss;

	if (m_Sign == 1 && (m_Count != 1 || m_Digits[0] != 0))
		ss << '-';
	for (int i = m_Count - 1; i >= 0; i--)
		ss << (int)m_Digits[i];

	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Integer& k)
{
	os << k.ToString();
	return os;
}