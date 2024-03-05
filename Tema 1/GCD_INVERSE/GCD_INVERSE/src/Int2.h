#pragma once
#include "Writer.h"


class Int2
{
public:
	Int2(long long x = 0, long long y = 0);
	Int2(const Int2& other) = default;
	Int2& operator=(const Int2& other) = default;
	~Int2() = default;

	long long GetX() const;
	long long GetY() const;

	std::string ToString() const;

	friend Int2 operator+(const Int2& v1, const Int2& v2);
	friend Int2 operator-(const Int2& v1, const Int2& v2);
	friend Int2 operator*(long long scalar, const Int2& v);
	friend Int2 operator*(const Int2& v, long long scalar);

	friend std::ostream& operator<<(std::ostream& output, const Int2& v);
private:
	long long m_X, m_Y;
};