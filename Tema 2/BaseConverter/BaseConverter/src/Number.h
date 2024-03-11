#pragma once
#include <iostream>


class Number
{
public:
	Number(uint32_t base, unsigned long long base10Number);
	Number(uint32_t base, const std::string& number);
	Number(const Number& other);
	Number& operator=(const Number& other);
	~Number();

	uint8_t& operator[](uint32_t index);
	uint8_t operator[](uint32_t index) const;

	unsigned long long ToInteger() const;
	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& os, const Number& n);
private:
	uint32_t m_Base;
	uint32_t m_DigitCount;
	uint8_t* m_Digits;
};