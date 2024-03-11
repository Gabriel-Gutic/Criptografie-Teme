#include "Number.h"

#include <sstream>


Number::Number(uint32_t base, unsigned long long base10Number)
    :m_Base(base), m_DigitCount(0), m_Digits(nullptr)
{
    m_DigitCount = base10Number == 0 ? 1 : ((int)(log(base10Number) / log(base)) + 1);

    m_Digits = new uint8_t[m_DigitCount];

    if (base10Number == 0)
    {
        m_Digits[0] = 0;
        return;
    }
    int i = 0;
    while (base10Number > 0)
    {
        m_Digits[i] = base10Number % base;
        base10Number /= base;
        i++;
    }
}

Number::Number(uint32_t base, const std::string& number)
    :m_Base(base), m_DigitCount(number.size()), m_Digits(nullptr)
{
    m_Digits = new uint8_t[m_DigitCount];

    for (uint32_t i = 0; i < m_DigitCount; i++)
    {
        uint32_t j = m_DigitCount - i - 1;

        if (!('0' <= number[i] && number[i] <= '9' ||
            'A' <= number[i] && number[i] <= 'Z' ||
            'a' <= number[i] && number[i] <= 'z'))
        {
            std::cout << "ERROR: Invalid character in number: '" << number[i] << "'" << std::endl;
            __debugbreak();
        }

        if ('0' <= number[i] && number[i] <= '9')
        {
            if (m_Base == 26 || number[i] - '0' >= m_Base)
            {
                std::cout << "ERROR: Invalid character in number: '" << number[i] << "'" << std::endl;
                __debugbreak();
            }
            m_Digits[j] = number[i] - '0';
        }
        else if ('A' <= number[i] && number[i] <= 'Z')
        {
            if (m_Base < 26)
            {
                if (number[i] - 'A' + 10 >= m_Base)
                {
                    std::cout << "ERROR: Invalid character in number: '" << number[i] << "'" << std::endl;
                    __debugbreak();
                }
                m_Digits[j] = number[i] - 'A' + 10;
            }
            else
            {
                m_Digits[j] = number[i] - 'A';
            }
        }
        else if ('a' <= number[i] && number[i] <= 'z')
        {
            if (m_Base < 26)
            {
                if (number[i] - 'a' + 10 >= m_Base)
                {
                    std::cout << "ERROR: Invalid character in number: '" << number[i] << "'" << std::endl;
                    __debugbreak();
                }
                m_Digits[j] = number[i] - 'a' + 10;
            }
            else
            {
                m_Digits[j] = number[i] - 'a';
            }
        }
    }
}

Number::Number(const Number& other)
    :m_Base(other.m_Base), m_DigitCount(other.m_DigitCount), m_Digits(nullptr)
{
    m_Digits = new uint8_t[m_DigitCount];
    
    for (int i = 0; i < m_DigitCount; i++)
        m_Digits[i] = other.m_Digits[i];
}

Number& Number::operator=(const Number& other)
{
    if (this != &other)
    {
        m_DigitCount = other.m_DigitCount;
        m_Digits = new uint8_t[m_DigitCount];

        for (int i = 0; i < m_DigitCount; i++)
            m_Digits[i] = other.m_Digits[i];
    }
    return *this;
}

Number::~Number()
{
    delete[] m_Digits;
}

uint8_t& Number::operator[](uint32_t index)
{
    if (index > m_DigitCount)
    {
        std::cout << "Index out of range." << std::endl;
        __debugbreak();
    }

    return m_Digits[index];
}

uint8_t Number::operator[](uint32_t index) const
{
    if (index > m_DigitCount)
    {
        std::cout << "ERROR: Index out of range." << std::endl;
        __debugbreak();
    }

    return m_Digits[index];
}

unsigned long long Number::ToInteger() const
{
    unsigned long long result = 0;
    unsigned long long power = 1;

    for (uint32_t i = 0; i < m_DigitCount; i++)
    {
        result += m_Digits[i] * power;
        power *= m_Base;
    }

    return result;
}

std::string Number::ToString() const
{
    std::stringstream ss;

    for (int i = m_DigitCount - 1; i >= 0; i--)
    {
        if (m_Base == 26)
        {
            ss << (char)(m_Digits[i] + 'A');
        }
        else
        {
            if (0 <= m_Digits[i] && m_Digits[i] <= 9)
            {
                ss << (int)m_Digits[i];
            }
            else if (10 <= m_Digits[i] && m_Digits[i] <= 26)
            {
                ss << (char)(m_Digits[i] + 'A' - 10);
            }
        }
    }

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Number& n)
{
    os << n.ToString();
    return os;
}
